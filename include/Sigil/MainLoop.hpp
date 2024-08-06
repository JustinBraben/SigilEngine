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
        bool running;
    };
}

#endif // SIGIL_MAIN_LOOP_HPP