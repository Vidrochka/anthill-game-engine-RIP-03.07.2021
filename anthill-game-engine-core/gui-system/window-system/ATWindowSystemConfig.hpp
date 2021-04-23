#ifndef at_window_system_config
#define at_window_system_config

#include "../../../third-party-libs/json/single_include/nlohmann/json.hpp"
#include "../../../anthill-game-engine-utils//types/ATString.hpp"

using json = nlohmann::json;

namespace at::core::gui::window_system::config
{
	struct WindowSystemConfig
	{
		at::type::string::u8string_at log_file_name;
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(WindowSystemConfig, log_file_name)
	};
}

#endif // at_window_system_config
