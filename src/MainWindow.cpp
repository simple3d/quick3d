#include "MainWindow.h"

#include "ThreeDWindow.h"
#include <nanogui/window.h>
#include <nanogui/layout.h>
#include <nanogui/button.h>
#include <GLFW/glfw3.h>

using namespace nanogui;

MainWindow::MainWindow() : 
    nanogui::Screen(Vector2i(800, 600), "Quick3D", true),
    m_serialPort(nullptr)
{
    Window* window = new Window(this, "Quick3D Child Window");
    window->set_position(Vector2i(15, 15));
    window->set_layout(new GroupLayout());

    m_canvas = new ThreeDWindow(window);
    m_canvas->set_background_color({ 100, 100, 100, 255 });
    m_canvas->set_size({ 700, 500 });

    Widget* tools = new Widget(window);
    tools->set_layout(new BoxLayout(Orientation::Horizontal,
        Alignment::Middle, 0, 5));

    Button* b0 = new Button(tools, "Connect");
    b0->set_callback(std::bind(&MainWindow::on_connect, this));

    Button* b1 = new Button(tools, "Read");
    b1->set_callback(std::bind(&MainWindow::on_read, this));

    perform_layout();
}

bool MainWindow::keyboard_event(int key, int scancode, int action, int modifiers) 
{
    if (Screen::keyboard_event(key, scancode, action, modifiers))
        return true;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        set_visible(false);
        return true;
    }
    return false;
}

void MainWindow::draw(NVGcontext* ctx) 
{
    // Draw the user interface
    Screen::draw(ctx);
}

void MainWindow::on_connect()
{
    m_canvas->set_background_color(
        Vector4i(rand() % 256, rand() % 256, rand() % 256, 255));
}

void MainWindow::on_read()
{
    m_canvas->set_rotation((float)3.14159 * rand() / (float)RAND_MAX);
}