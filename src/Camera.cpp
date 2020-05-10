#include "Camera.h"

Vector4f mul(const Matrix4f& m, const Vector4f& v)
{
    Vector4f result = Vector4f(0.f, 0.f, 0.f, 0.f);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result[i] += m.m[j][i] * v[j];
        }
    }
    return result;
}

Camera::Camera() :
    m_origin(0.f, 0.f, -10.f),
    m_target(0.f, 0.f, 0.f),
    m_up(0.f, 1.f, 0.f),
    m_fov(25.f * 3.14159f / 180.f),
    m_near(0.1f),
    m_far(20.f),
    m_size(480, 640)
{
}

Matrix4f Camera::GetProjectionMatrix() const
{
    return Matrix4f::perspective(
        m_fov,
        m_near,
        m_far,
        m_size.x() / (float)m_size.y()
    );
}

Matrix4f Camera::GetViewMatrix() const
{
    return Matrix4f::look_at(m_origin, m_target, m_up);
}

void Camera::LookAt(const Vector3f& origin, const Vector3f& target, const Vector3f& up)
{
    m_origin = origin;
    m_target = target;
    m_up = up;
}

void Camera::SetFov(float fov)
{
    m_fov = fov;
}

void Camera::SetNear(float _near)
{
    m_near = _near;
}

void Camera::SetFar(float _far)
{
    m_far = _far;
}

void Camera::SetSize(const Vector2i& size)
{
    m_size = size;
}

const Vector2i& Camera::GetSize() const
{
    return m_size;
}

void Camera::RotateHorizontally(float angle)
{
    Matrix4f rotation = Matrix4f::rotate(m_up, angle);
    Vector3f origin_to_target = m_origin - m_target;
    Vector4f origin_to_target4 = Vector4f(origin_to_target[0], origin_to_target[1], origin_to_target[2], 1.f);
    Vector4f new_origin_to_target4;
    new_origin_to_target4 = mul(rotation, origin_to_target4);
    Vector3f new_origin_to_target(new_origin_to_target4[0], new_origin_to_target4[1], new_origin_to_target4[2]);
    m_origin = m_target + new_origin_to_target;
}

void Camera::RotateVertically(float angle)
{
    Vector3f origin_to_target = normalize(m_origin - m_target);
    Vector3f horizontal = cross(normalize(m_up), origin_to_target);
    normalize(horizontal);
    Matrix4f rotation = Matrix4f::rotate(horizontal, angle);
    origin_to_target = m_origin - m_target;
    Vector4f origin_to_target4 = Vector4f(origin_to_target[0], origin_to_target[1], origin_to_target[2], 1.f);
    Vector4f new_origin_to_target4;
    new_origin_to_target4 = mul(rotation, origin_to_target4);
    Vector3f new_origin_to_target(new_origin_to_target4[0], new_origin_to_target4[1], new_origin_to_target4[2]);
    m_origin = m_target + new_origin_to_target;
}
