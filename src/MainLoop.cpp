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

             SDL_Event evnt;
             while (SDL_PollEvent(&evnt))
             {

             }

             for (auto& it : m_processList)
             {
                 auto& handler = get<0>(it);
                 auto& timer = get<1>(it);

                 handler(timer.getTicks());
                 timer.start();
             }
         }
    }

    void MainLoop::quit() 
    {
        m_running = false;
    }

} // namespace Sigil