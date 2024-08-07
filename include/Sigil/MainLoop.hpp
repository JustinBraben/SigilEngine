#ifndef SIGIL_MAIN_LOOP_HPP
#define SIGIL_MAIN_LOOP_HPP

#include <Sigil/Timer.hpp>

#include <iostream>
#include <functional>
#include <tuple>
#include <list>

namespace Sigil 
{
    using ProcessHandler = std::function<void(int)>;

    using ProcessEntry = std::tuple<ProcessHandler, Timer>;

    class MainLoop 
    {
    public:
        MainLoop();

        void processListHandler(ProcessHandler handler);
        void processDelistHandler(ProcessHandler handler);

        void run();
        void quit();
    private:
        bool m_running;
        Timer m_fpsTimer;

        std::list<ProcessEntry> m_processList;
    };
} // namespace Sigil

#endif // SIGIL_MAIN_LOOP_HPP