#include <DXExtensions.hpp>
#include <DXShared.hpp>

namespace at::core::gui::render::directx
{
    auto get_max_support_dx_version(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device) -> D3D_FEATURE_LEVEL {
        return get_max_support_dx_version(d3d12_device, 
        {
            D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_9_1,
            D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_9_2,
            D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_9_3,
            D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_1_0_CORE,
            D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_0,
            D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_12_1,
        });
    }

    auto get_max_support_dx_version(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device, std::vector<D3D_FEATURE_LEVEL> dx_required_version) -> D3D_FEATURE_LEVEL {
        D3D12_FEATURE_DATA_FEATURE_LEVELS data{};
        data.NumFeatureLevels = dx_required_version.size();
        data.pFeatureLevelsRequested = &dx_required_version[0];
        shared::throw_if_fail(d3d12_device->CheckFeatureSupport(D3D12_FEATURE_FEATURE_LEVELS, &data, sizeof(data)));
        return data.MaxSupportedFeatureLevel;
    }

    auto create_command_queue(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device, D3D12_COMMAND_LIST_TYPE commad_list_type, D3D12_COMMAND_QUEUE_FLAGS flags) -> Microsoft::WRL::ComPtr<ID3D12CommandQueue> {
        Microsoft::WRL::ComPtr<ID3D12CommandQueue> command_queue;

        D3D12_COMMAND_QUEUE_DESC queue_desc{};
        queue_desc.Type = commad_list_type;
        queue_desc.Flags = flags;
        shared::throw_if_fail(d3d12_device->CreateCommandQueue(&queue_desc, IID_PPV_ARGS(&command_queue)));
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> l;
        return command_queue;
    }

    auto get_gpu_device_count(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device) -> uint16_t {
        return static_cast<uint16_t>(d3d12_device->GetNodeCount());
    }

    auto create_debug_controller() -> Microsoft::WRL::ComPtr<ID3D12Debug> {
        Microsoft::WRL::ComPtr<ID3D12Debug> debug_controller;
        shared::throw_if_fail(D3D12GetDebugInterface(IID_PPV_ARGS(&debug_controller)));
        return debug_controller;
    }
    
    auto create_dx_device(D3D_FEATURE_LEVEL feature_level, IDXGIAdapter* adapted) -> Microsoft::WRL::ComPtr<ID3D12Device> {
        Microsoft::WRL::ComPtr<ID3D12Device> d3d_device;
        shared::throw_if_fail(D3D12CreateDevice( nullptr,  feature_level, IID_PPV_ARGS(&d3d_device)));
        return d3d_device;
    }

    auto create_fence(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device) -> Microsoft::WRL::ComPtr<ID3D12Fence> {
        Microsoft::WRL::ComPtr<ID3D12Fence> fence;
        shared::throw_if_fail(d3d12_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence)));
        return fence;
    }

    auto get_msaa_quality(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device, UINT sample_count, DXGI_FORMAT back_buffer_format, D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS flags) -> UINT {
        D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS ms_quality_levels;
        ms_quality_levels.Format = back_buffer_format;
        ms_quality_levels.SampleCount = sample_count;
        ms_quality_levels.Flags = flags;
        ms_quality_levels.NumQualityLevels = 0;

        shared::throw_if_fail(d3d12_device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &ms_quality_levels, sizeof(ms_quality_levels)));

        return ms_quality_levels.NumQualityLevels;
    }

    auto create_command_queue(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device, D3D12_COMMAND_LIST_TYPE command_list_type, D3D12_COMMAND_QUEUE_FLAGS flags) -> Microsoft::WRL::ComPtr<ID3D12CommandQueue> {
        Microsoft::WRL::ComPtr<ID3D12CommandQueue> command_queue;
        
        D3D12_COMMAND_QUEUE_DESC queue_desc = {};
        queue_desc.Type = command_list_type;
        queue_desc.Flags = flags;

        shared::throw_if_fail(d3d12_device->CreateCommandQueue(&queue_desc,  IID_PPV_ARGS(&command_queue)));

        return command_queue;
    }

    auto create_comand_allocator(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device, D3D12_COMMAND_LIST_TYPE type) -> Microsoft::WRL::ComPtr<ID3D12CommandAllocator> {
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmd_list_alloc;

        shared::throw_if_fail(d3d12_device->CreateCommandAllocator(type,  IID_PPV_ARGS(cmd_list_alloc.GetAddressOf())));

        return cmd_list_alloc;
    }

    auto create_comand_list(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device, Microsoft::WRL::ComPtr<ID3D12CommandAllocator>& cmd_list_alloc, D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE_DIRECT) -> Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> {
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_list;

        shared::throw_if_fail(d3d12_device->CreateCommandList(0, type, cmd_list_alloc.Get(), nullptr, IID_PPV_ARGS(command_list.GetAddressOf())));
        command_list->Close();
        return command_list;
    }

    auto create_rtv_heap(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device, UINT swap_chain_buffer_count, D3D12_DESCRIPTOR_HEAP_FLAGS flags) -> Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> {
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtv_heap;

        D3D12_DESCRIPTOR_HEAP_DESC rtv_heap_desc;
        rtv_heap_desc.NumDescriptors = swap_chain_buffer_count;
        rtv_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtv_heap_desc.Flags = flags;
        rtv_heap_desc.NodeMask = 0;

        shared::throw_if_fail(d3d12_device->CreateDescriptorHeap(&rtv_heap_desc, IID_PPV_ARGS(rtv_heap.GetAddressOf())));

        return rtv_heap;
    }

    auto create_dsv_heap(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device, UINT swap_chain_buffer_count, D3D12_DESCRIPTOR_HEAP_FLAGS flags) -> Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> {
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsv_heap;

        D3D12_DESCRIPTOR_HEAP_DESC dsv_heap_desc;
        dsv_heap_desc.NumDescriptors = swap_chain_buffer_count;
        dsv_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
        dsv_heap_desc.Flags = flags;
        dsv_heap_desc.NodeMask = 0;

        shared::throw_if_fail(d3d12_device->CreateDescriptorHeap(&dsv_heap_desc, IID_PPV_ARGS(dsv_heap.GetAddressOf())));

        return dsv_heap;
    }

    auto get_buffer_view(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtv_heap, UINT back_buffer_id, UINT rtv_descriptor_size) -> D3D12_CPU_DESCRIPTOR_HANDLE {
        return CD3DX12_CPU_DESCRIPTOR_HANDLE(rtv_heap->GetCPUDescriptorHandleForHeapStart(), back_buffer_id, rtv_descriptor_size);
    }

    auto get_stencil_view(Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsv_heap) -> D3D12_CPU_DESCRIPTOR_HANDLE {
        return dsv_heap->GetCPUDescriptorHandleForHeapStart();
    }

    auto create_swapchain_buffers(Microsoft::WRL::ComPtr<ID3D12Device>& d3d12_device, Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain, D3D12_CPU_DESCRIPTOR_HANDLE rtv_heap_handle, UINT rtv_descriptor_size, UINT buffers_count) -> Microsoft::WRL::ComPtr<ID3D12Resource>* {
        Microsoft::WRL::ComPtr<ID3D12Resource>* swap_chain_buffers = new Microsoft::WRL::ComPtr<ID3D12Resource>[buffers_count];

        for (UINT i = 0; i < buffers_count; i++)
        {
            shared::throw_if_fail(swap_chain->GetBuffer(i, IID_PPV_ARGS(&swap_chain_buffers[i])));
            d3d12_device->CreateRenderTargetView(swap_chain_buffers[i].Get(), nullptr, rtv_heap_handle);

            static_cast<CD3DX12_CPU_DESCRIPTOR_HANDLE>(rtv_heap_handle).Offset(1, rtv_descriptor_size);
        }

        return swap_chain_buffers;
    }
}