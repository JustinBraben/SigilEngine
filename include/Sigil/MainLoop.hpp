#ifndef SIGIL_MAIN_LOOP_HPP
#define SIGIL_MAIN_LOOP_HPP

#include <iostream>

namespace Sigil {
    class MainLoop {
    public:
        MainLoop();

        void run();
        void quit();
    private:
        bool m_running;
    };
} // namespace Sigil

#endif // SIGIL_MAIN_LOOP_HPP