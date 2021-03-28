#ifndef at_config_parsing_strategy
#define at_config_parsing_strategy

#include "ATConfig.hpp"
#include "ATConfigSource.hpp"

using namespace at::utils::config_manager::config::interface;
using namespace at::utils::config_manager::source::interface;

namespace at::utils::config_manager::parsing_strategy
{
    namespace interface
    {
        class IParsingStrategy
        {
        public:
            virtual IConfig *get_config(IConfigSourceInterface *config_source) = 0;
        };
    }

    class TomlParsingStrategy : public interface::IParsingStrategy
    {
    public:
        IConfig *get_config(IConfigSourceInterface *config_source) override;
    };
}

#endif