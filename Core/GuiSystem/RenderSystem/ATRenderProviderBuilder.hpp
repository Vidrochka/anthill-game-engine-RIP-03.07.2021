#ifndef at_render_provider_builder
#define at_render_provider_builder

#include "ATRenderProvider.hpp"
#include "../../../Utils/Utils.hpp"
#include "RenderProviderImplementation/ATOpenglRenderProvider.hpp"

namespace at::core::gui::render
{
    enum class RENDER_PROVIDER_TYPE
    {
        DEFAULT = 0,
        OPENGL,
        VULKAN,
        METAL
    };

    NLOHMANN_JSON_SERIALIZE_ENUM (RENDER_PROVIDER_TYPE, {
        {RENDER_PROVIDER_TYPE::DEFAULT, "default"},
        {RENDER_PROVIDER_TYPE::OPENGL, "opengl"},
        {RENDER_PROVIDER_TYPE::VULKAN, "vulkan"},
        {RENDER_PROVIDER_TYPE::METAL, "metal"},
    })

    using namespace at::utils::log_system::logger::at_interface;

    static at_interface::IRenderProvider* get_render_provider(RENDER_PROVIDER_TYPE render_provider_type, std::shared_ptr<ILogger> logger, SDL_Window *window)
    {
        switch(render_provider_type)
        {
            case RENDER_PROVIDER_TYPE::DEFAULT:
                return new OpenglRenderProvider(logger, window);
            case RENDER_PROVIDER_TYPE::OPENGL:
                return new OpenglRenderProvider(logger, window);
            case RENDER_PROVIDER_TYPE::VULKAN:
                return nullptr;
            case RENDER_PROVIDER_TYPE::METAL:
                return nullptr;
        }
    } 
}

#endif //at_render_provider_builder