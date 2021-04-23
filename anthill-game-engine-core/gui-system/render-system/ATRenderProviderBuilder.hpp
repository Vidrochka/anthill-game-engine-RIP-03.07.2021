#ifndef at_render_provider_builder
#define at_render_provider_builder

#include "ATRenderProvider.hpp"
//#include "RenderProviderImplementation/ATOpenglRenderProvider.hpp"
//#include "RenderProviderImplementation/ATVulkanRenderProvider.hpp"
//#include "RenderProviderImplementation/ATDirectX12RenderProvider.hpp"

#include "../../../anthill-game-engine-utils/log-system/ATLogger.hpp"

#include "../../../anthill-game-engine-utils//types/ATString.hpp"



namespace at::core::gui::render
{
    using namespace at::utils::log_system::logger::at_interface;

    static at_interface::IRenderProvider* get_render_provider(RENDER_PROVIDER_TYPE render_provider_type, std::shared_ptr<ILogger> logger, SDL_Window *window)
    {
        switch(render_provider_type)
        {
            case RENDER_PROVIDER_TYPE::DEFAULT:
                return nullptr; // new VulkanRenderProvider(logger, window);
            case RENDER_PROVIDER_TYPE::OPENGL:
                return nullptr; // new OpenglRenderProvider(logger, window);
            case RENDER_PROVIDER_TYPE::VULKAN:
                return nullptr; // new VulkanRenderProvider(logger, window);
            case RENDER_PROVIDER_TYPE::DX12:
                return nullptr; // new DirectX12RenderProvider(logger, window);
            case RENDER_PROVIDER_TYPE::METAL:
                return nullptr;
        }
    } 
}

#endif //at_render_provider_builder