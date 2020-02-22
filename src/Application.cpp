#include "Application.h"
#include "MainWindow.h"

Application::Application()
{
    nanogui::init();
}

Application::~Application()
{
    nanogui::shutdown();
}

void Application::Run()
{
    nanogui::ref<MainWindow> mainWindow = new MainWindow();
    mainWindow->draw_all();
    mainWindow->set_visible(true);
    nanogui::mainloop(1 / 60.f * 1000);
}
