#ifndef at_window_manager
#define at_window_manager

#include "../../third_party_libs/SDL2-2.0.14/include/SDL.h"
#include "../../Utils/Utils.hpp"
#include "ATWindowContext.hpp"
#include "ATWindowInitializeSettings.hpp"
#include "ATPreloadWindowInitializeSettings.hpp"
#include <memory>
#include <map>
#include <mutex>
#include <tuple>

using namespace at::core::window_system::window_context;
using namespace at::core::window_system::window_initialize_settings;
using namespace at::core::window_system::preload_window_initialize_settings;
using namespace at::utils::log_system::logger::at_interface;

namespace at::core::window_system::window_manager
{

    namespace result
    {
        enum class WINDOW_CREATE_RESULT
        {
            OK = 0,
            UNKNOWN_ERROR,
            UNKNOWN_OPEN_MODE,
            UNKNOWN_RENDER_SYSTEM,
            WINDOW_ALREADY_EXIST,
        };

        enum class PRELOAD_WINDOW_CREATE_RESULT
        {
            OK = 0,
            UNKNOWN_ERROR,
            UNKNOWN_OPEN_MODE,
            UNKNOWN_RENDER_SYSTEM,
            WINDOW_ALREADY_EXIST,
        };
    }

    namespace at_interface
    {
        class IWindowManager
        {
        public:
            virtual ~IWindowManager(){};
            virtual auto open_preload_window(PreloadWindowInitializeSettings settings) -> result::PRELOAD_WINDOW_CREATE_RESULT = 0;
            virtual auto close_preload_window(u8string_at window_name) -> void = 0;
            virtual auto open_new_window(const WindowInitializeSettings settings) -> result::WINDOW_CREATE_RESULT = 0;
        };
    }

    class WindowManager : public at_interface::IWindowManager
    {
    private:
        WindowManager(WindowManager &);
        WindowManager &operator=(const WindowManager &){};

        std::map<u8string_at, WindowContext *> _window_map;
        std::shared_ptr<ILogger> _logger;

        std::mutex *_modify_window_collection_mx;

    public:
        WindowManager(std::shared_ptr<ILogger> logger);
        ~WindowManager() override;
        auto open_preload_window(PreloadWindowInitializeSettings settings) -> result::PRELOAD_WINDOW_CREATE_RESULT override;
        auto close_preload_window(u8string_at window_name) -> void override;
        auto open_new_window(const WindowInitializeSettings settings) -> result::WINDOW_CREATE_RESULT override;
    };
}

#endif