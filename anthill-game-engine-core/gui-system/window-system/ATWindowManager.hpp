#ifndef at_window_manager
#define at_window_manager

#include "ATWindow.hpp"
#include "ATWindowInitializeSettings.hpp"
#include "ATWindowSystemConfig.hpp"

#include "../render-system/ATRenderProviderBuilder.hpp"
#include "../render-system/ATRenderProvider.hpp"

#include "../widgets/ATWidget.hpp"

//#include "../../engine-core/ATEngineCore.hpp"

#include "../../../anthill-game-engine-utils/guid/ATGuid.hpp"
#include "../../../anthill-game-engine-utils/log-system/ATLogger.hpp"
#include "../../../anthill-game-engine-utils/log-system/ATLoggerManager.hpp"

#include "../../../third-party-libs/SDL2-2.0.14/include/SDL.h"

#include <memory>
#include <map>
#include <mutex>
#include <tuple>
#include <utility>

using namespace at::core::gui::window_system::window_context;
using namespace at::core::gui::window_system::window_initialize_settings;
using namespace at::utils::log_system::logger::at_interface;
using namespace at::utils::log_system::at_interface;
using namespace at::core::gui::widgets::at_interface;
//using namespace at::core::engine_core::at_interface;

namespace at::core::gui::window_system::window_manager
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
    }

    class WindowManager
    {
    private:
        WindowManager(WindowManager &) = delete;
        WindowManager &operator=(const WindowManager &) = delete;

        std::shared_ptr<ILoggerManager> _logger_manager;
        std::shared_ptr<ILogger> _window_system_logger;
        config::WindowSystemConfig _config;

        at::utils::guid::Guid<uint16_t> _window_id_fabric = at::utils::guid::Guid<uint16_t>();
        std::map<uint16_t, std::shared_ptr<Window>> _window_map;

        std::mutex* _modify_window_collection_mx;

    public:
        bool has_close_signal = false;

        WindowManager(std::shared_ptr<ILoggerManager> logger_manager, config::WindowSystemConfig config);
        ~WindowManager();
        auto process_events() -> void;
        //возврашает результат действия и id окна
        auto open_new_window(const WindowInitializeSettings settings, std::shared_ptr<IWidget> top_widget) -> std::shared_ptr<Window>;
    };
}

#endif