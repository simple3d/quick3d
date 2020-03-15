#pragma once

/// Encapsulation of the application itself
/// Declare an Application object and call Run.
/// Example:
/// Application myApplication;
/// myApplication.Run();
class Application
{
public:
    /// Constructor
    /// Does all the application start up.
    Application();
    /// Deconstructor
    /// Does all the application shut down.
    ~Application();
    /// The main call to run the application.
    /// Manages the main loop of the application.
    void Run();
};