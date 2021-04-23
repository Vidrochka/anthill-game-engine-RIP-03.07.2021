#include <DXGIExtensions.hpp>
#include <DXShared.hpp>

namespace at::core::gui::render::directx
{
    auto get_adapters_list(IDXGIFactory& dxgi_factory) -> std::vector<std::pair<IDXGIAdapter*, DXGI_ADAPTER_DESC*>> {
        UINT i = 0;
        IDXGIAdapter* adapter = nullptr;
        std::vector<std::pair<IDXGIAdapter*, DXGI_ADAPTER_DESC*>> adapters_list;
        while(dxgi_factory.EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND) {
            DXGI_ADAPTER_DESC* desc = new DXGI_ADAPTER_DESC{};
            adapter->GetDesc(desc);
            adapters_list.push_back({adapter, desc});
            ++i;
        }

        return adapters_list;
    }

    auto get_adapter_outputs_list(IDXGIAdapter& adapter) -> std::vector<std::pair<IDXGIOutput*, DXGI_OUTPUT_DESC*>> {
        UINT i = 0;
        IDXGIOutput* output = nullptr;     
        std::vector<std::pair<IDXGIOutput*, DXGI_OUTPUT_DESC*>> adapter_outputs_list;
        while(adapter.EnumOutputs(i, &output) != DXGI_ERROR_NOT_FOUND) {
            DXGI_OUTPUT_DESC* desc = new DXGI_OUTPUT_DESC{};
            output->GetDesc(desc);
            adapter_outputs_list.push_back({output,desc});
            ++i;
        }

        return adapter_outputs_list;
    }

    auto get_output_display_modes(IDXGIOutput* output, DXGI_FORMAT format) -> std::vector<DXGI_MODE_DESC> {
        UINT count = 0;
        UINT flags = 0;
        // Call with nullptr to get list count.
        output->GetDisplayModeList(format, flags, &count, nullptr);
        std::vector<DXGI_MODE_DESC> modeList(count);
        output->GetDisplayModeList(format, flags, &count, &modeList[0]);
        return modeList;
    }

    auto create_dxgi_factory() -> Microsoft::WRL::ComPtr<IDXGIFactory> {
        Microsoft::WRL::ComPtr<IDXGIFactory> dxgi_factory;
        shared::throw_if_fail(CreateDXGIFactory1(IID_PPV_ARGS(&dxgi_factory)));

        return dxgi_factory;
    }

    auto create_swap_chain(Microsoft::WRL::ComPtr<IDXGIFactory>& dxgi_factory, Microsoft::WRL::ComPtr<ID3D12CommandQueue>& command_queue,
        UINT width, UINT height, UINT rate_numerator, INT rate_denominator, DXGI_FORMAT format, UINT sample_count, UINT msaa_quality, 
        HWND win_desc, UINT swap_chain_buffer_count, DXGI_SWAP_CHAIN_FLAG flags) -> Microsoft::WRL::ComPtr<IDXGISwapChain> 
    {
        Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain;
        swap_chain.Reset(); //maby rudement

        DXGI_SWAP_CHAIN_DESC swap_chain_desc;
        swap_chain_desc.BufferDesc.Width = width;
        swap_chain_desc.BufferDesc.Height = height;
        swap_chain_desc.BufferDesc.RefreshRate.Numerator = rate_numerator;
        swap_chain_desc.BufferDesc.RefreshRate.Denominator = rate_denominator;
        swap_chain_desc.BufferDesc.Format = format;
        swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        swap_chain_desc.SampleDesc.Count = sample_count;
        swap_chain_desc.SampleDesc.Quality = msaa_quality;
        swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_desc.BufferCount = swap_chain_buffer_count;
        swap_chain_desc.OutputWindow = win_desc;
        swap_chain_desc.Windowed = true;
        swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swap_chain_desc.Flags = flags;

        shared::throw_if_fail(dxgi_factory->CreateSwapChain(command_queue.Get(), &swap_chain_desc, swap_chain.GetAddressOf()));

        return swap_chain;
    }
}