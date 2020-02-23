/* Copyright © 2020 simple3d. All rights reserved.
/ See LICENSE.txt for details.
*/
/** \file */
#pragma once

#include <nanogui/canvas.h>

using nanogui::Shader;
using nanogui::Canvas;
using nanogui::ref;

/**
 * \class Label label.h nanogui/label.h
 *
 * \brief Text label widget.
 *
 * The font and color can be customized. When \ref Widget::set_fixed_width()
 * is used, the text is wrapped when it surpasses the specified width.
 */
class ThreeDWindow : public Canvas {
public:
    ThreeDWindow(Widget* parent);

    void set_rotation(float rotation);

    virtual void draw_contents() override;

private:
    ref<Shader> m_shader;
    float m_rotation;
};
