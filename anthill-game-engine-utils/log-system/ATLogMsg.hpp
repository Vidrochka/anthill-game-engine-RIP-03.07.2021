#ifndef at_log_msg
#define at_log_msg

#include "../types/ATString.hpp"

#include "../../third-party-libs/boost_1_75_0/boost/stacktrace.hpp"

using namespace at::type::string;
using namespace at::utils::log_system::event;

namespace at::utils::log_system::log_msg
{
	struct LogMsg
	{
		u8string_at msg;
		EVENT_TYPE event_type;
		bool has_error_code = false;
		int error_code;
		bool has_stack_trace = false;
		boost::stacktrace::stacktrace stack_trace;
	};
}

#endif // at_log_msg