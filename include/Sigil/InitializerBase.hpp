#ifndef SIGIL_INITIALIZER_BASE_HPP
#define SIGIL_INITIALIZER_BASE_HPP

namespace Sigil {
    class InitializerBase
    {
    public:
        InitializerBase();

        virtual void doInitialize() = 0;
        virtual void doShutdown() = 0;

        void initialize();
        void shutdown();

        bool isInitialized() const;
        bool isFreed() const;

    private:
        bool initialized;
        bool freed;
    };
}

#endif // SIGIL_INITIALIZER_BASE_HPP