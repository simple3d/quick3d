#pragma once

#include <nanogui/canvas.h>

using nanogui::Shader;
using nanogui::Canvas;
using nanogui::ref;

/// The class for the window where the 3D drawing is happening.
class ThreeDWindow : public Canvas {
public:
    ThreeDWindow(Widget* parent);

    void set_rotation(float rotation);

    virtual void draw_contents() override;

private:
    ref<Shader> m_shader;
    float m_rotation;
};
