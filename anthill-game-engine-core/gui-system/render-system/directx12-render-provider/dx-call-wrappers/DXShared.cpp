#include <DXExceptions.hpp>
#include <DXShared.hpp>

namespace at::core::gui::render::directx::shared
{
    auto throw_if_fail(HRESULT result) -> void {
        if(result != S_OK)
            throw exceptions::directx_exception(static_cast<int64_t>(result));
    }
}