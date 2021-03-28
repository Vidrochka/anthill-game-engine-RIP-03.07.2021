#ifndef at_config_manager
#define at_config_manager

#include "ATConfigParsingStrategy.hpp"
#include "ATConfigSource.hpp"
#include "ATConfig.hpp"

using namespace at::utils::config_manager::source::interface;
using namespace at::utils::config_manager::config::interface;
using namespace at::utils::config_manager::parsing_strategy::interface;

namespace at::utils::config_manager
{
    class ConfigManager
    {
    public:
        static IConfig *get_config(IConfigSourceInterface *config_source, IParsingStrategy *parsing_strategy);
    };
}

#endif