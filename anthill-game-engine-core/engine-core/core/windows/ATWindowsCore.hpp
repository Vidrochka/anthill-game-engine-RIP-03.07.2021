#ifndef at_windows_core
#define at_windows_core

#include "../../ATEngineCore.hpp"
#include "../../../../anthill-game-engine-utils//log-system/ATLogger.hpp"
#include "../../../../anthill-game-engine-utils/log-system/ATLoggerManager.hpp"
#include "ATWindowsCoreConfig.hpp"
#include "../../../gui-system/window-system/ATWindowManager.hpp"

#include <memory>

using namespace at::utils::log_system::logger::at_interface;
using namespace at::utils::log_system::at_interface;
using namespace at::core::gui::window_system::window_manager;

namespace at::core::engine_core
{
	class WindowsEngineCore : public at_interface::IEngineCore
	{
	private:
		config::WindowsCoreConfig _core_config;

		std::shared_ptr<WindowManager> _window_manager;

		std::shared_ptr<ILoggerManager> _logger_manager;
		std::shared_ptr<ILogger> _core_logger;
		std::shared_ptr<ILogger> _window_system_logger;

	protected:
		auto initialize_core() -> void override;
		auto initialize_systems() -> void override;
		auto initialize_modules() -> void override;
		auto run_sycle() -> void override;

	public:
		WindowsEngineCore();
		~WindowsEngineCore();
	};
}

#endif // at_windows_core
