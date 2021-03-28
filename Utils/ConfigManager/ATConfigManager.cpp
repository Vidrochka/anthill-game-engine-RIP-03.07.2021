#include "ATConfigManager.hpp"

using namespace at::utils::config_manager::source::interface;
using namespace at::utils::config_manager::config::interface;
using namespace at::utils::config_manager::parsing_strategy::interface;

namespace at::utils::config_manager
{
    IConfig *ConfigManager::get_config(IConfigSourceInterface *config_source, IParsingStrategy *parsing_strategy)
    {
        return parsing_strategy->get_config(config_source);
    }
}