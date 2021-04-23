#ifndef dxgi_extensions
#define dxgi_extensions

#include <d3d12.h>
#include <dxgi.h>
#include <utility>
#include <vector>
#include <wrl\module.h>

namespace at::core::gui::render::directx
{
    template<typename T>
    auto release_come_objects_and_descriptors_list(std::vector<T*> adapters_list) -> void {
        for(T &output : adapters_list)
        {
            delete output.second;
            output.first->Release();
        }

        adapter_outputs_list.clear();
    }

    auto get_adapters_list(IDXGIFactory& dxgi_factory) -> std::vector<std::pair<IDXGIAdapter*, DXGI_ADAPTER_DESC*>>;

    auto get_adapter_outputs_list(IDXGIAdapter& adapter) -> std::vector<std::pair<IDXGIOutput*, DXGI_OUTPUT_DESC*>>;

    auto get_output_display_modes(IDXGIOutput* output, DXGI_FORMAT format) -> std::vector<DXGI_MODE_DESC>;

    auto create_dxgi_factory() -> Microsoft::WRL::ComPtr<IDXGIFactory>;

    auto create_swap_chain(Microsoft::WRL::ComPtr<IDXGIFactory>& dxgi_factory, Microsoft::WRL::ComPtr<ID3D12CommandQueue>& command_queue,
        UINT width, UINT height, UINT rate_numerator, UINT rate_denominator, DXGI_FORMAT format, UINT sample_count, UINT msaa_quality,
        HWND win_desc, UINT swap_chain_buffer_count, DXGI_SWAP_CHAIN_FLAG flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH) -> Microsoft::WRL::ComPtr<IDXGISwapChain>;
}

#endif //dxgi_extensions