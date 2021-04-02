#ifndef at_config_manager
#define at_config_manager

#include "ATConfigParsingStrategy.hpp"
#include "ATConfigSource.hpp"
#include "ATConfig.hpp"

using namespace at::utils::config_system::source::at_interface;
using namespace at::utils::config_system::config::at_interface;
using namespace at::utils::config_system::parsing_strategy::at_interface;

namespace at::utils::config_system
{
    class ConfigManager
    {
    public:
        static IConfig *get_config(IConfigSourceInterface *config_source, IParsingStrategy *parsing_strategy);
    };
}

#endif