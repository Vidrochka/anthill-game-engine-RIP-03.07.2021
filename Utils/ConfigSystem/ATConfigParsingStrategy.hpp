#ifndef at_config_parsing_strategy
#define at_config_parsing_strategy

#include "ATConfig.hpp"
#include "ATConfigSource.hpp"
#include "../Types/ATString.hpp"

using namespace at::utils::config_system::config::at_interface;
using namespace at::utils::config_system::source::at_interface;
using namespace at::type::string;

namespace at::utils::config_system::parsing_strategy
{
    namespace at_interface
    {
        class IParsingStrategy
        {
        public:
            virtual ~IParsingStrategy() {}
            virtual IConfig *get_config(IConfigSourceInterface *config_source) = 0;
        };
    }

    class TomlParsingStrategy : public at_interface::IParsingStrategy
    {
    public:
        ~TomlParsingStrategy() override {}
        IConfig *get_config(IConfigSourceInterface *config_source) override;
    };
}

#endif