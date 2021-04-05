#define DEBUG_UTILS

//--------------Logging--------------//
#include "LogSystem/ATLoggerEvent.hpp"
#include "LogSystem/ATLogger.hpp"
#include "LogSystem/ATLoggerContext.hpp"
#include "LogSystem/ATLoggerDefineExtensions.hpp"

#include "LogSystem/ATLoggerExceptions.hpp"
#include "LogSystem/ATLoggerManager.hpp"
#include "LogSystem/ATLoggerStrategy.hpp"

//--------------Castom types--------------//
#include "Types/ATColor.hpp"
#include "Types/ATString.hpp"

//--------------File parsing--------------//
#include "../third_party_libs/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;