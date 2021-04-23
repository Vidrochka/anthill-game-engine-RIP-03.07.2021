#include "ATDirectX12RenderProvider.hpp"
#include "dx-call-wrappers/DXExtensions.hpp"
#include "dx-call-wrappers/DXGIExtensions.hpp"
#include <utility>
#include <SDL_syswm.h>

namespace at::core::gui::render
{
    DirectX12RenderProvider::DirectX12RenderProvider(std::shared_ptr<ILogger> logger, SDL_Window *window) : at_interface::IRenderProvider(logger, window) {
#ifdef _DEBUG
        _debug_controller = directx::create_debug_controller();
        _debug_controller->EnableDebugLayer();
#endif

        _dxgi_factiry = directx::create_dxgi_factory();
        _d3d12_device = directx::create_dx_device(D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_0);
        _fence = directx::create_fence(_d3d12_device);

        _descriptor_heap_type_rtv_size = _d3d12_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        _descriptor_heap_type_dsv_size = _d3d12_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
        _descriptor_heap_type_cbv_srv_size = _d3d12_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

        _4x_msaa_quality = directx::get_msaa_quality(_d3d12_device, _sample_count, _back_buffer_format);

        _command_queue = directx::create_command_queue(_d3d12_device);
        _command_allocator = directx::create_comand_allocator(_d3d12_device);
        _graphics_command_list = directx::create_comand_list(_d3d12_device, _command_allocator);

        int width, height;
        SDL_GetWindowSize(_window, &width, &height);

        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);
        SDL_GetWindowWMInfo(window, &wmInfo);
        HWND hwnd = (HWND)wmInfo.info.win.window;

        _swap_chain = directx::create_swap_chain(_dxgi_factiry, _command_queue, width, height, _rate_numerator,
            _rate_denominator, _back_buffer_format, _sample_count, _4x_msaa_quality, hwnd, _swap_chain_buffer_count);

        _rtv_heap = directx::create_rtv_heap(_d3d12_device, _swap_chain_buffer_count);
        _dsv_heap = directx::create_dsv_heap(_d3d12_device, _swap_chain_buffer_count);
        
        _current_back_buffer_view = directx::get_buffer_view(_rtv_heap, _current_back_buffer, _descriptor_heap_type_rtv_size);
        _current_depth_stencil_view = directx::get_stencil_view(_dsv_heap);

        _swap_chin_buffers = directx::create_swapchain_buffers(_d3d12_device, _swap_chain, _current_back_buffer_view, 
            _descriptor_heap_type_rtv_size, _swap_chain_buffer_count);
    }

    DirectX12RenderProvider::~DirectX12RenderProvider() {
        delete _swap_chin_buffers;
    }

    auto DirectX12RenderProvider::draw_rectangle() -> void {
    }

    auto DirectX12RenderProvider::draw_triangle() -> void {
    }

    auto DirectX12RenderProvider::draw_circle() -> void {
    }

    auto DirectX12RenderProvider::draw_text() -> void {
    }

    auto DirectX12RenderProvider::draw_line() -> void {
    }

    auto DirectX12RenderProvider::draw_frame() -> void {
    }

    auto DirectX12RenderProvider::draw_image(/*std::shared_ptr<type::image::Image> image,*/ uint_fast32_t shader_program_id/*, Rect<int_fast32_t> rect*/) -> void {
    }

    auto DirectX12RenderProvider::add_shader(std::ifstream& shader_stream, SHADER_TYPE shader_type) -> uint_fast32_t{
        return 1;
    }

    auto DirectX12RenderProvider::add_shader(u8string_at shader_file_name, SHADER_TYPE shader_type) -> uint_fast32_t {
        return 1;
    }

    auto DirectX12RenderProvider::add_shader(std::stringstream& shader_stream, SHADER_TYPE shader_type) -> uint_fast32_t {
        return 1;
    }

    auto DirectX12RenderProvider::delete_shader(uint_fast32_t shader_id, SHADER_TYPE shader_type) -> void {
    }

    auto DirectX12RenderProvider::add_shaders_program(std::map<SHADER_TYPE, uint_fast32_t> shaders_id_map) -> uint_fast32_t {
        return 1;
    }

    auto DirectX12RenderProvider::delete_shaders_program(uint_fast32_t shader_program_id) -> void {
    }

    auto DirectX12RenderProvider::initialize_render_context(SDL_Window &window) -> void {
    }

    auto DirectX12RenderProvider::select_render_context() -> void {
    }

    auto DirectX12RenderProvider::prepare_new_frame(at::type::color::RGBA_at<uint8_t> color) -> void {
        //SDL_GetWindowSize(_window, &_width, &_height);
    }
}