#include <Sigil/InitializerBase.hpp>

namespace Sigil {
    InitializerBase::InitializerBase()
        : initialized(false), freed(true) {}

    void InitializerBase::initialize()
    {

    }

    void InitializerBase::shutdown()
    {

    }

    bool InitializerBase::isInitialized() const
    {

    }

    bool InitializerBase::isFreed() const
    {

    }
}