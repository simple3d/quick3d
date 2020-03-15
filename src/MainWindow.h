#pragma once

#include <nanogui/screen.h>

class ThreeDWindow;

/// The main window of the application
class MainWindow : public nanogui::Screen 
{
public:
    /// Constructor
    MainWindow();

    /// Called when a keyboard key is pressed.
    virtual bool keyboard_event(int key, int scancode, int action, int modifiers) override;
    /// Called to draw the window.
    virtual void draw(NVGcontext* ctx) override;

    /// Handler for the connect button.
    void on_connect();
    /// Handler for the read button.
    void on_read();

private:
    ThreeDWindow* m_canvas;
};
