#include "ATLoggerStrategyUtils.hpp"

#include <ctime>

namespace at::utils::log_system::strategy::log_utils
{
    auto _get_datetime_prefix() -> u8string_at {
        time_t now = time(0);
#pragma warning(suppress : 4996)
        std::string raw_dt{ctime(&now)};
        u8string_at s_dt = u8string_at(raw_dt.begin(), raw_dt.end());
        return "["u8at + s_dt.substr(0, s_dt.length() - 1) + "]"u8at;
    }
}