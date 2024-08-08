#include <Sigil/MainLoop.hpp>

namespace Sigil {

    template<typename T, typename... U>
    static bool functionsEqual(std::function<T(U...)> lhs, std::function<T(U...)> rhs)
    {
        using FunctionPtr = T(*)(U...);

        FunctionPtr** plhs = lhs.template target<FunctionPtr*>();
        FunctionPtr** prhs = rhs.template target<FunctionPtr*>();

        return (*plhs) == (*prhs);
    }

    MainLoop::MainLoop()
        : m_running(false) {}

    void MainLoop::sinkEventQuit()
    {
        m_eventDispatcher.sink<Event_Quit>().connect<&EventListener::HandleQuit>(m_eventListener);
    }

    void MainLoop::processListHandler(ProcessHandler handler)
    {
        Timer timer;
        timer.start();

        m_processList.push_back(std::make_tuple(std::move(handler), std::move(timer)));
    }

    void MainLoop::processDelistHandler(ProcessHandler handler)
    {
        for (auto it = m_processList.begin(); it != m_processList.end(); it++)
        {
            if (functionsEqual(std::get<0>(*it), handler))
            {
                m_processList.erase(it);
            }
        }
    }

    void MainLoop::run() 
    {
        m_running = true;
        std::cout << "MainLoop::run() called\n";

         // While running handle events, until quit
         while (m_running)
         {
             m_fpsTimer.start();
             
             //SDL_Event evnt;
             //while (SDL_PollEvent(&evnt))
             //{
             //    // m_eventDispatcher.enqueue<SDL_Event>(evnt);
             //    /*switch (evnt.type)
             //    {
             //    case SDL_EventType::SDL_QUIT:
             //        m_eventDispatcher.enqueue<Event_Quit>();
             //        m_running = false;
             //        break;
             //    default:
             //        break;
             //    }*/

             //    /*m_sceneManager.getCurrentScene()->actionManager().eventHandler(&evnt);*/
             //}
             SDL_Event evnt;
             SDL_PollEvent(&evnt);
             m_sceneManager.getCurrentScene()->actionManager().eventHandler(&evnt);

             if (m_sceneManager.getCurrentScene()->actionManager().isPressed("ui_quit"))
             {
                 m_running = false;
             }



             m_eventDispatcher.update();
         }
    }

    void MainLoop::quit() 
    {
        m_running = false;
    }

    SceneManager& MainLoop::sceneManager()
    {
        return m_sceneManager;
    }

} // namespace Sigil