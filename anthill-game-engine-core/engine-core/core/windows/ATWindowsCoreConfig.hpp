#ifndef at_windows_core_config
#define at_windows_core_config

#include "../../../../third-party-libs/json/single_include/nlohmann/json.hpp"
#include "../../../../anthill-game-engine-utils//types/ATString.hpp"

using json = nlohmann::json;

namespace at::core::engine_core::config
{
	struct WindowsCoreConfig
	{
	public:
		at::type::string::u8string_at log_file_name;
		at::type::string::u8string_at window_system_config_file_path;
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(WindowsCoreConfig, log_file_name, window_system_config_file_path)
	};
}

#endif // at_windows_core_config