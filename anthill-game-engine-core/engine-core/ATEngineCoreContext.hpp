#ifndef at_engine_core_context
#define at_engine_core_context

#include "../../anthill-game-engine-utils/log-system/ATLoggerManager.hpp"

#include <memory>

using namespace at::utils::log_system::at_interface;

namespace at::core::engine_core
{
	struct EngineContext
	{
		std::atomic<std::shared_ptr<ILoggerManager>> _logger_manager;
	};
}

#endif //at_engine_core_context