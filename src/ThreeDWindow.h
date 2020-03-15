#pragma once

#include <nanogui/canvas.h>

using nanogui::Shader;
using nanogui::Canvas;
using nanogui::ref;

/// The class for the window where the 3D drawing is happening.
class ThreeDWindow : public Canvas {
public:
    /// Constructor
    ThreeDWindow(Widget* parent);

    /// Called to change the rotation.
    void set_rotation(float rotation);

    /// Called to draw the contents of the 3D view.
    virtual void draw_contents() override;

private:
    ref<Shader> m_shader;
    float m_rotation;
};
