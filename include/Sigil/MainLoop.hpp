#ifndef SIGIL_MAIN_LOOP_HPP
#define SIGIL_MAIN_LOOP_HPP

namespace Sigil {
    class MainLoop {
    public:
        MainLoop(int fps);

        void run();
        void quit();
    private:
        int fps;
        bool running;
    };
}

#endif // SIGIL_MAIN_LOOP_HPP