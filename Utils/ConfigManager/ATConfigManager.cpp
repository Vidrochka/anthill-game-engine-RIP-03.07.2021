#include "ATConfigManager.hpp"

using namespace at::utils::config_manager::source::at_interface;
using namespace at::utils::config_manager::config::at_interface;
using namespace at::utils::config_manager::parsing_strategy::at_interface;

namespace at::utils::config_manager
{
    IConfig *ConfigManager::get_config(IConfigSourceInterface *config_source, IParsingStrategy *parsing_strategy)
    {
        return parsing_strategy->get_config(config_source);
    }
}