#ifndef at_engine_core_fabric
#define at_engine_core_fabric

#include "ATEngineCore.hpp"
#include "core/windows/ATWindowsCore.hpp"
#include "../../anthill-game-engine-utils/types/ATString.hpp"
#include <string>
#include <memory>

namespace at::core::engine_core
{
	inline static auto get_engine_core() -> std::shared_ptr<at_interface::IEngineCore> {
#if defined(WIN32) || defined(_WIN32)
		return std::shared_ptr<at_interface::IEngineCore>(new WindowsEngineCore());
#else
		static_assert(false, "Not supported system");
#endif // WIN32/_WIN32
	}
}

#endif // at_engine_core_fabric
