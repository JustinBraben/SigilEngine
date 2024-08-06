#ifndef SIGIL_TIMER_HPP
#define SIGIL_TIMER_HPP

#include <SDL2/SDL.h>

namespace Sigil
{
    class Timer 
    {
    public:
        Timer();
        ~Timer() = default;

        void start();

        Uint64 getTicks();
    private:
        Uint64 m_ticks;
    };
} // namespace Sigil


#endif // SIGIL_TIMER_HPP