#ifndef SIGIL_MAIN_LOOP_HPP
#define SIGIL_MAIN_LOOP_HPP

#include <Sigil/Scene/SceneManager.hpp>
#include <Sigil/Timer.hpp>
#include <Sigil/Event/EventListener.hpp>
#include <Sigil/Event/EventTypes.hpp>

#include <iostream>
#include <functional>
#include <tuple>
#include <list>

#include <entt/entt.hpp>

namespace Sigil 
{
    using EventHandler = std::function<bool(SDL_Event*)>;
    using ProcessHandler = std::function<void(int)>;

    using ProcessEntry = std::tuple<ProcessHandler, Timer>;

    class MainLoop 
    {
    public:
        MainLoop();

        void sinkEventQuit();

        //template<typename EventType, typename EventListenerType>
        //void sinkEvent(EventListenerType& listener)
        //{
        //    // m_eventDispatcher.sink<EventType>().connect<&EventListener::HandleQuit>(m_eventListener);
        //    // Connect the event handler to the dispatcher sink for the specified event type
        //    m_eventDispatcher.sink<EventType>().template connect<&EventListenerType::HandleEvent>(listener);
        //}

        void processListHandler(ProcessHandler handler);
        void processDelistHandler(ProcessHandler handler);

        void run();
        void quit();

        entt::dispatcher            m_eventDispatcher;
        Sigil::EventListener        m_eventListener;

    private:
        bool m_running;
        Timer m_fpsTimer;


        std::list<ProcessEntry>     m_processList;
    };
} // namespace Sigil

#endif // SIGIL_MAIN_LOOP_HPP