#ifndef dx_extensions
#define dx_extensions

#include <d3d12.h>
#include <d3dx12.h>
#include <dxgi.h>
#include <utility>
#include <vector>
#include <memory>
#include <wrl\module.h>

namespace at::core::gui::render::directx
{
    auto get_max_support_dx_version(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device) -> D3D_FEATURE_LEVEL;

    auto get_max_support_dx_version(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device, std::vector<D3D_FEATURE_LEVEL> dx_required_version) -> D3D_FEATURE_LEVEL;

    auto create_command_queue(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device,
        D3D12_COMMAND_LIST_TYPE commad_list_type = D3D12_COMMAND_LIST_TYPE_DIRECT,
        D3D12_COMMAND_QUEUE_FLAGS flags = D3D12_COMMAND_QUEUE_FLAG_NONE) -> Microsoft::WRL::ComPtr<ID3D12CommandQueue>;

    auto get_gpu_device_count(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device) -> uint16_t;

    auto create_debug_controller() -> Microsoft::WRL::ComPtr<ID3D12Debug>;

    auto create_dx_device(D3D_FEATURE_LEVEL feature_level, IDXGIAdapter* adapted = nullptr) -> Microsoft::WRL::ComPtr<ID3D12Device>;

    auto create_fence(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device) -> Microsoft::WRL::ComPtr<ID3D12Fence>;

    auto get_msaa_quality(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device, UINT sample_count, DXGI_FORMAT back_buffer_format, D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE) -> UINT;

    auto create_command_queue(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device, D3D12_COMMAND_LIST_TYPE command_list_type = D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12_COMMAND_QUEUE_FLAGS flags = D3D12_COMMAND_QUEUE_FLAG_NONE) -> Microsoft::WRL::ComPtr<ID3D12CommandQueue>;

    auto create_comand_allocator(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device, D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE_DIRECT) -> Microsoft::WRL::ComPtr<ID3D12CommandAllocator>;

    auto create_comand_list(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device, Microsoft::WRL::ComPtr<ID3D12CommandAllocator>& cmd_list_alloc, D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE_DIRECT) -> Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>;

    auto create_rtv_heap(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device, UINT swap_chain_buffer_count, D3D12_DESCRIPTOR_HEAP_FLAGS flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE) -> Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>;

    auto create_dsv_heap(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device, UINT swap_chain_buffer_count, D3D12_DESCRIPTOR_HEAP_FLAGS flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE) -> Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>;

    auto get_buffer_view(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtv_heap, UINT back_buffer_id, UINT rtv_descriptor_size) -> D3D12_CPU_DESCRIPTOR_HANDLE;

    auto get_stencil_view(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsv_heap) -> D3D12_CPU_DESCRIPTOR_HANDLE;

    auto create_swapchain_buffers(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device, Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain, D3D12_CPU_DESCRIPTOR_HANDLE rtv_heap_handle, UINT rtv_descriptor_size, UINT buffers_count) -> Microsoft::WRL::ComPtr<ID3D12Resource>*;
}

#endif //dx_extensions