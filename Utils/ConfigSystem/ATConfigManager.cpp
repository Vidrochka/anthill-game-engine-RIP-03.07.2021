#include "ATConfigManager.hpp"

using namespace at::utils::config_system::source::at_interface;
using namespace at::utils::config_system::config::at_interface;
using namespace at::utils::config_system::parsing_strategy::at_interface;

namespace at::utils::config_system
{
    IConfig *ConfigManager::get_config(IConfigSourceInterface *config_source, IParsingStrategy *parsing_strategy)
    {
        config_source->reset();
        return parsing_strategy->get_config(config_source);
    }
}