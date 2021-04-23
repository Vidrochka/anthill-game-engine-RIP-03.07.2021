#ifndef at_guid
#define at_guid
#include "ATGuidExceptions.hpp"
#include <cassert>
#include <type_traits>
#include <limits>
#include <set>
#include <mutex>
//#include <algorithm>

#undef max
#undef min

namespace at::utils::guid
{
    template <typename id_type>
    class Guid
    {
    protected:
        id_type guid_ptr = std::numeric_limits<id_type>::min();
        //std::list<id_type> _released_collection{};
        std::set<id_type> _released_collection{};
        std::mutex _modification_mutex{};
        
    public:
        Guid() {
            //_modification_mutex = new std::mutex();
            static_assert(std::is_integral<id_type>());
        }

        ~Guid(){
            //delete _modification_mutex;
        }

        virtual auto release_id(id_type id) -> void {
            std::lock_guard<std::mutex> lg(_modification_mutex);

            if (id == (guid_ptr - 1)) // if id is last taken
                guid_ptr--;
            else
                _released_collection.insert(id);
                //_released_collection.push_back(id);
        }

        virtual auto get_new_id() -> id_type {
            std::lock_guard<std::mutex> lg(_modification_mutex);

            if(!_released_collection.empty()) { // reuse released id
                //id_type reused_val = _released_collection.back();
                //_released_collection.pop_back();
                id_type reused_val = *(--(_released_collection.end()));
                _released_collection.erase(--(_released_collection.end()));
                return reused_val;
            }

            if(guid_ptr == std::numeric_limits<id_type>::max()) // if we have no uniqe value for type
                throw guid::exceptions::guid_overflow<id_type>();
            
            return guid_ptr++;
        }

        virtual auto defragmentate() -> int_fast64_t {
            std::lock_guard<std::mutex> lg(_modification_mutex);

            if (_released_collection.size() == 0)
                return 0;

            int_fast64_t iteration_counter = 0;

            //_released_collection.sort();
            //std::sort(std::begin(_released_collection), std::end(_released_collection));
            //_released_collection.sort();

            auto last_element = *(--(_released_collection.end()));
            //auto last_element = _released_collection.back();

            while(last_element == guid_ptr-1){ // if id is last taken
                --guid_ptr;
                //_released_collection.pop_back();
                _released_collection.erase(--(_released_collection.end()));
                //last_element = _released_collection.back();
                last_element = *(--(_released_collection.end()));
                ++iteration_counter;
            }

            return iteration_counter;
        }
    };
}

#endif