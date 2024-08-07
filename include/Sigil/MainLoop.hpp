#ifndef SIGIL_MAIN_LOOP_HPP
#define SIGIL_MAIN_LOOP_HPP

#include <Sigil/Timer.hpp>

#include <iostream>
#include <functional>
#include <tuple>
#include <list>

#include <entt/signal/dispatcher.hpp>

namespace Sigil 
{
    using EventHandler = std::function<bool(SDL_Event*)>;
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

        entt::dispatcher            m_eventDispatcher;
        std::list<ProcessEntry>     m_processList;
    };
} // namespace Sigil

#endif // SIGIL_MAIN_LOOP_HPP