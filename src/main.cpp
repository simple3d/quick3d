#include "Application.h"

#include <stdexcept>
#include <iostream>

/// The main function where execution begins.
/// Declare an Application object and call Run.
/// Catch exceptions in case problems occur in the constructor or deconstructor.
int main(int /* argc */, char ** /* argv */) 
{
    try {
        Application quick3d;
        quick3d.Run();
    } catch (const std::runtime_error &e) {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
        std::cerr << error_msg << std::endl;
        return -1;
    }
    return 0;
}
