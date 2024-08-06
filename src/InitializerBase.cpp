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
        return false;
    }

    bool InitializerBase::isFreed() const
    {
        return false;
    }
} // namespace Sigil