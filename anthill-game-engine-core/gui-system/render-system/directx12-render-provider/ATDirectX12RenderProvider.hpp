#ifndef at_directx12_render_provider
#define at_directx12_render_provider

#include "../ATRenderProvider.hpp"
#include "../../../../third-party-libs/SDL2-2.0.14/include/SDL.h"
#include <utility>
#include <wrl\module.h>
#include <d3d12.h>
#include <dxgi.h>

//NDEBUG

namespace at::core::gui::render
{
    class DirectX12RenderProvider : public at_interface::IRenderProvider
    {
    private:
        Microsoft::WRL::ComPtr<ID3D12Debug> _debug_controller = nullptr;
        Microsoft::WRL::ComPtr<IDXGIFactory> _dxgi_factiry = nullptr;
        Microsoft::WRL::ComPtr<ID3D12Device> _d3d12_device = nullptr;
        Microsoft::WRL::ComPtr<ID3D12Fence> _fence = nullptr;
        Microsoft::WRL::ComPtr<ID3D12CommandQueue> _command_queue = nullptr;
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> _command_allocator = nullptr;
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> _graphics_command_list = nullptr;
        Microsoft::WRL::ComPtr<IDXGISwapChain> _swap_chain = nullptr;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _rtv_heap = nullptr;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> _dsv_heap = nullptr;

        uint32_t _descriptor_heap_type_rtv_size;
        uint32_t _descriptor_heap_type_dsv_size;
        uint32_t _descriptor_heap_type_cbv_srv_size;

        DXGI_FORMAT _back_buffer_format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
        uint32_t _sample_count = 4;
        uint32_t _4x_msaa_quality;

        const uint32_t _rate_numerator = 60;
        const uint32_t _rate_denominator = 1;
        const uint32_t _swap_chain_buffer_count = 2;
        Microsoft::WRL::ComPtr<ID3D12Resource>* _swap_chin_buffers;
        uint32_t _current_back_buffer = 0;

        D3D12_CPU_DESCRIPTOR_HANDLE _current_back_buffer_view;
        D3D12_CPU_DESCRIPTOR_HANDLE _current_depth_stencil_view;

    public:
        DirectX12RenderProvider(std::shared_ptr<ILogger> logger, SDL_Window *window);
        ~DirectX12RenderProvider() override;
        auto draw_rectangle() -> void override;
        auto draw_triangle() -> void override;
        auto draw_circle() -> void override;
        auto draw_text() -> void override;
        auto draw_line() -> void override;
        auto draw_frame() -> void override;
        auto draw_image(/*std::shared_ptr<type::image::Image> image,*/ uint_fast32_t shader_program_id/*, Rect<int_fast32_t> rect*/) -> void override;
        auto add_shader(std::ifstream& shader_stream, SHADER_TYPE shader_type) -> uint_fast32_t override;
        auto add_shader(u8string_at shader_file_name, SHADER_TYPE shader_type) -> uint_fast32_t override;
        auto add_shader(std::stringstream& shader_stream, SHADER_TYPE shader_type) -> uint_fast32_t override;
        auto delete_shader(uint_fast32_t shader_id, SHADER_TYPE shader_type) -> void override;
        auto add_shaders_program(std::map<SHADER_TYPE, uint_fast32_t> shaders_id_map) -> uint_fast32_t override;
        auto delete_shaders_program(uint_fast32_t shader_program_id) -> void override;
        auto initialize_render_context(SDL_Window &window) -> void override;
        auto select_render_context() -> void override;
        auto prepare_new_frame(at::type::color::RGBA_at<uint8_t> color) -> void override;
    };
}

#endif //at_directx12_render_provider