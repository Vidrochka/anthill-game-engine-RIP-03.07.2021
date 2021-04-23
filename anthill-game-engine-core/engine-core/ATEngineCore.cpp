#include "ATEngineCore.hpp"

namespace at::core::engine_core::at_interface
{
	auto IEngineCore::run() -> void
	{
		initialize_core();
		initialize_systems();
		initialize_modules();
		run_sycle();
	}
}