#include <Sigil/Timer.hpp>

namespace Sigil
{
    Timer::Timer()
        : ticks(0) {}

    void Timer::start()
    {
        ticks = SDL_GetPerformanceCounter();
    }

    Uint64 Timer::getTicks()
    {
        return SDL_GetPerformanceCounter() - ticks;
    }
} // namespace Sigil