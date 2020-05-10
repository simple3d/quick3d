#include "ThreeDWindow.h"

#include <stdexcept>
#include <iostream>
#include <nanogui/shader.h>
#include <GLFW/glfw3.h>

using namespace nanogui;

ThreeDWindow::ThreeDWindow(Widget* parent) : 
    Canvas(parent, 1)
{
    m_camera.LookAt(
        Vector3f(0, -2, -10),
        Vector3f(0, 0, 0),
        Vector3f(0, 1, 0)
    );
    m_camera.SetFov(25.f * 3.14159f / 180.f);
    m_camera.SetNear(0.1f);
    m_camera.SetFar(20.f);
    m_camera.SetSize(m_size);

    try
    {
        std::cout << "Compiling shaders..." << std::endl;
        m_shader = new Shader(
            render_pass(),

            // An identifying name
            "a_simple_shader",

#if defined(NANOGUI_USE_OPENGL)
            // Vertex shader
            R"(#version 330
            uniform mat4 mvp;
            in vec3 position;
            in vec3 normal;
            in vec3 color;
            out vec4 frag_color;
            out vec3 frag_normal;
            void main() {
                frag_color = vec4(color, 1.0);
                frag_normal = normalize(mat3(mvp) * normal);
                gl_Position = mvp * vec4(position, 1.0);
            })",

            // Fragment shader
            R"(#version 330
            out vec4 color;
            in vec4 frag_color;
            in vec3 frag_normal;
            void main() {
                color = frag_color*abs(frag_normal.z);
            })"
#elif defined(NANOGUI_USE_GLES)
            // Vertex shader
            R"(precision highp float;
            uniform mat4 mvp;
            attribute vec3 position;
            attribute vec3 color;
            varying vec4 frag_color;
            void main() {
                frag_color = vec4(color, 1.0);
                gl_Position = mvp * vec4(position, 1.0);
            })",

            // Fragment shader
            R"(precision highp float;
            varying vec4 frag_color;
            void main() {
                gl_FragColor = frag_color;
            })"
#elif defined(NANOGUI_USE_METAL)
            // Vertex shader
            R"(using namespace metal;

            struct VertexOut {
                float4 position [[position]];
                float4 color;
            };

            vertex VertexOut vertex_main(const device packed_float3 *position,
                                         const device packed_float3 *color,
                                         constant float4x4 &mvp,
                                         uint id [[vertex_id]]) {
                VertexOut vert;
                vert.position = mvp * float4(position[id], 1.f);
                vert.color = float4(color[id], 1.f);
                return vert;
            })",

            /* Fragment shader */
            R"(using namespace metal;

            struct VertexOut {
                float4 position [[position]];
                float4 color;
            };

            fragment float4 fragment_main(VertexOut vert [[stage_in]]) {
                return vert.color;
            })"
#endif
        );
    }
    catch (std::runtime_error err)
    {
        printf("Exception: %s\n", err.what());
        throw err;
    }
    std::cout << "Done compiling shaders..." << std::endl;

    std::cout << "Preparing buffers..." << std::endl;

    uint32_t indices[3 * 2] = {
        0, 1, 2,
        0, 2, 3
    };

    float positions[3 * 4] = {
        -1.f, -1.f, 0.f, 
        1.f, -1.f, 0.f,
        1.f, 1.f, 0.f,
        -1.f, 1.f, 0.f
    };

    float normals[3 * 4] = {
        0.f, 0.f, 1.f,
        0.f, 0.f, 1.f,
        0.f, 0.f, 1.f,
        0.f, 0.f, 1.f
    };

    float colors[3 * 4] = {
        0, 1, 1, 0, 0, 1,
        1, 0, 1, 1, 1, 1,
    };

    m_shader->set_buffer("indices", VariableType::UInt32, { 3 * 2 }, indices);
    m_shader->set_buffer("position", VariableType::Float32, { 4, 3 }, positions);
    m_shader->set_buffer("normal", VariableType::Float32, { 4, 3 }, normals);
    m_shader->set_buffer("color", VariableType::Float32, { 4, 3 }, colors);

    std::cout << "Buffers ready..." << std::endl;

}

bool ThreeDWindow::mouse_drag_event(const Vector2i& p, const Vector2i& rel, int button, int modifiers)
{
    float relxf = ((float) rel.x()) / ((float) m_size.x());
    float relyf = ((float) rel.y()) / ((float) m_size.y());
    m_camera.RotateVertically(relyf * 3.14159f);
    m_camera.RotateHorizontally(relxf * 3.14159f);
    return false;
}

void ThreeDWindow::draw_contents() 
{
    m_camera.SetSize(m_size);

    Matrix4f view = m_camera.GetViewMatrix();
    Matrix4f proj = m_camera.GetProjectionMatrix();

    Matrix4f mvp = proj * view;

    m_shader->set_uniform("mvp", mvp);

    glDisable(GL_CULL_FACE);
     
    // Draw 12 triangles starting at index 0
    m_shader->begin();
    m_shader->draw_array(Shader::PrimitiveType::Triangle, 0, 12 * 3, true);
    m_shader->end();
}
