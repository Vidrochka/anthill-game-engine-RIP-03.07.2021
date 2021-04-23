#include "ATWindowsCore.hpp"
#include "../../../../anthill-game-engine-utils/log-system/ATLoggerStrategy.hpp" 
#include "../../../../anthill-game-engine-utils/log-system/log-strategy/ATFileLogStrategy.hpp"
#include "../../../../anthill-game-engine-utils/log-system/log-strategy/ATConsoleLogStrategy.hpp"

#include "../../../gui-system/window-system/ATWindowSystemConfig.hpp"
#include "../../../gui-system/window-system/ATWindowInitializeSettings.hpp"

#include <iostream>
#include <exception>
#include "../../../gui-system/widgets/ATFrameWidget.hpp"

using namespace at::utils::log_system::strategy;
using namespace at::utils::log_system;
using namespace at::core::gui::window_system::config;
using namespace at::core::gui::window_system::window_initialize_settings;
using namespace at::core::gui::widgets;

namespace at::core::engine_core
{
	auto get_error_log()->std::shared_ptr<at::utils::log_system::logger::at_interface::ILogger>;

	auto WindowsEngineCore::initialize_core() -> void {
	}

	auto WindowsEngineCore::initialize_systems() -> void {
		try {
			std::ifstream window_system_config_file(_core_config.window_system_config_file_path);

			if (!window_system_config_file.is_open())
				throw std::runtime_error(U8StringBuilder{ "Core cant open file [{0}]. Maby file not exist"u8at }.fmt(0, _core_config.window_system_config_file_path));

			json window_system_json_conf_repr;
			window_system_config_file >> window_system_json_conf_repr;
			auto window_system_config = window_system_json_conf_repr["window_system"u8at].get<WindowSystemConfig>();

			_window_manager = std::shared_ptr<WindowManager>(new WindowManager(std::shared_ptr<ILoggerManager>(_logger_manager), window_system_config));

			auto window_preload_config = window_system_json_conf_repr["preload_window_settings"u8at].get<WindowInitializeSettings>();
			_window_manager->open_new_window(window_preload_config, std::shared_ptr<FrameWidget>(new FrameWidget()));
		}
		catch (std::exception ex) {
			_core_logger->log_fatal("Window system creating fail: "u8at + ex.what(), -1);
			throw ex;
		}
	}

	auto WindowsEngineCore::initialize_modules() -> void {
	}

	auto WindowsEngineCore::run_sycle() -> void {
		while (!_window_manager->has_close_signal)
		{
			_window_manager->process_events();
			//_core_logger->log_debug("Sycle processed");
		}
	}

	WindowsEngineCore::WindowsEngineCore() {
		try {
			std::ifstream main_config("windows_core.cfg.json"u8at);

			if (!main_config.is_open())
				throw std::runtime_error("Core cant open file [windows_core.cfg.json]. Maby file not exist");

			json json_conf_repr;
			main_config >> json_conf_repr;
			_core_config = json_conf_repr["windows_core"u8at].get<config::WindowsCoreConfig>();
		}
		catch (std::exception ex) {
			auto logger = get_error_log();
			logger->log_fatal("Windows core creating fail: "u8at + ex.what(), -1);
			throw ex;
		}

		_logger_manager = std::shared_ptr<ILoggerManager>(new LoggerManager());
		_logger_manager->create_logger("core_logger", std::shared_ptr<ILogStrategy>(new FileLogStrategy(_core_config.log_file_name, 0)));
		_core_logger = _logger_manager->get_logger("core_logger");
		_core_logger->add_strategy(std::shared_ptr<ILogStrategy>(new ConsoleLogStrategy(0)));
		_core_logger->log_info("Windows engine core created");
	}

	WindowsEngineCore::~WindowsEngineCore() {
		_core_logger->log_info("Windows engine core destroyed");
	}

	auto get_error_log() -> std::shared_ptr<ILogger> {
		auto logger_manager = std::shared_ptr<ILoggerManager>(new LoggerManager());
		logger_manager->create_logger("error_core_init"u8at, std::shared_ptr<ILogStrategy>(new FileLogStrategy("error_core_init.log"u8at, 0)));
		auto logger = logger_manager->get_logger("error_core_init"u8at);
		logger->add_strategy(std::shared_ptr<ILogStrategy>(new ConsoleLogStrategy(0)));
		return logger;
	}
}