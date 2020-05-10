#pragma once

#include <nanogui/canvas.h>
#include "Camera.h"

using nanogui::Shader;
using nanogui::Canvas;
using nanogui::ref;

/// The class for the window where the 3D drawing is happening.
class ThreeDWindow : public Canvas {
public:
    /// Constructor
    ThreeDWindow(Widget* parent);

    /// Responds to the mouse drag event.
    virtual bool mouse_drag_event(const Vector2i& p, const Vector2i& rel, int button, int modifiers) override;

    /// Called to draw the contents of the 3D view.
    virtual void draw_contents() override;

private:
    ref<Shader> m_shader;
    Camera m_camera;
};
