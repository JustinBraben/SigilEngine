#include <Sigil/MainLoop.hpp>

namespace Sigil {

    MainLoop::MainLoop(int fps)
        : fps(fps), running(false) {}

    void MainLoop::run() 
    {
        running = true;

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