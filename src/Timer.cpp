#include <Sigil/Timer.hpp>

namespace Sigil
{
    Timer::Timer()
        : m_ticks(0) {}

    void Timer::start()
    {
        m_ticks = SDL_GetPerformanceCounter();
    }

    Uint64 Timer::getTicks()
    {
        return SDL_GetPerformanceCounter() - m_ticks;
    }
} // namespace Sigil