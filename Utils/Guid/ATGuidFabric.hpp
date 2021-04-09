#ifndef at_guid_fabric
#define at_guid_fabric

#include "../../Defines.hpp"

#ifdef DEBUG_UTILS
    #include "ATDebugGuid.hpp"
    #include "../LogSystem/ATLoggerManager.hpp"
#endif

#include "ATGuid.hpp"


namespace at::utils::guid
{
    /*template<typename id_type>
    Guid<id_type> get_new_guid()
    {
#ifdef DEBUG_UTILS
    at::utils::log_system::LoggerManager log_manager{};
    log_manager.create_logger("guid_ligger"u8at, new at::utils::log_system::strategy::DefaultFileLogStrategy("./guid_ligger.log"u8at, 0));
    auto logger = log_manager.get_logger("guid_ligger"u8at);
    return DebugGuid<id_type>(logger);
#else
    return Guid<id_type>{};
#endif
    }*/
}

#endif at_guid_fabric