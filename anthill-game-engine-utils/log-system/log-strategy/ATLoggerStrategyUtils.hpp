#ifndef at_logger_strategy_utils
#define at_logger_strategy_utils

#include "../../Types/ATString.hpp"
#include <ctime>

using namespace at::type::string;

namespace at::utils::log_system::strategy::log_utils
{
    auto _get_datetime_prefix() -> u8string_at;
}

#endif