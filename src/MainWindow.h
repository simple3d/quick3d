#pragma once

#include <nanogui/screen.h>

class ThreeDWindow;
class SerialPort;

// The main window of the application
class MainWindow : public nanogui::Screen 
{
public:
    MainWindow();

    virtual bool keyboard_event(int key, int scancode, int action, int modifiers) override;
    virtual void draw(NVGcontext* ctx) override;

    void on_connect();
    void on_read();

private:
    ThreeDWindow* m_canvas;
    SerialPort* m_serialPort;
};
