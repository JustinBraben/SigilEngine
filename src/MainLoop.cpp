#include <Sigil/MainLoop.hpp>

namespace Sigil {

    MainLoop::MainLoop()
        : running(false) {}

    void MainLoop::run() 
    {
        running = true;
        std::cout << "MainLoop::run() called\n";

        // // While running handle events, until quit
        // while (running)
        // {

        // }
    }

    void MainLoop::quit() 
    {
        running = false;
    }

} // namespace Sigil