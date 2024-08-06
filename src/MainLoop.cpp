#include <Sigil/MainLoop.hpp>

namespace Sigil {

    MainLoop::MainLoop()
        : m_running(false) {}

    void MainLoop::run() 
    {
        m_running = true;
        std::cout << "MainLoop::run() called\n";

        // // While running handle events, until quit
        // while (running)
        // {

        // }
    }

    void MainLoop::quit() 
    {
        m_running = false;
    }

} // namespace Sigil