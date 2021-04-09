#ifndef at_debug_guid
#define at_debug_guid
#include "ATGuidExceptions.hpp"
#include "../LogSystem/ATLogger.hpp"
#include "../Types/ATString.hpp"
#include <cassert>
#include <type_traits>
#include <limits>
#include <vector>
#include <mutex>
#include <memory>

namespace at::utils::guid
{
    /*template <typename id_type>
    class DebugGuid : public Guid
    {
    private:
        std::shared_ptr<log_system::logger::at_interface::ILogger> _logger;
        
    public:
        DebugGuid( std::shared_ptr<log_system::logger::at_interface::ILogger> logger) : Guid<id_type>() {
            _logger = logger;
        }

        auto release_id(id_type id) -> id_type override {
            _logger->log_debug("Release id ["u8at + std::to_string(id) + "]"u8at);
            return Guid::release_id();
        }

        auto get_new_id() -> id_type override {
            id_type id = Guid::get_new_id();
            _logger->log_debug("Get new id ["u8at + std::to_string(id) + "]"u8at);
            return id
        }

        auto defragmentate() -> int_fast64_t override {
            int_fast64_t defragmentation_id_count = Guid::defragmentate();
            _logger->log_debug("Defragmentate id collection, id count ["u8at + std::to_string(defragmentation_id_count) + "]"u8at);
            return defragmentation_id_count;
        }
    };*/
}

#endif