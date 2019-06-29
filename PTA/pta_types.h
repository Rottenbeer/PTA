#pragma once

enum pta_log_level_t
{
    PTA_LOG_DEBUG,   //!< Debug level.
    PTA_LOG_INFO,    //!< Info level.
    PTA_LOG_WARNING, //!< Warning level.
    PTA_LOG_CRITICAL //!< Critical level.
};

// Config defs
constexpr auto PTA_CONFIG_LOGLEVEL = "global/loglevel";
constexpr auto PTA_CONFIG_LOGFILE  = "global/logfile";

constexpr auto PTA_CONFIG_DISPLAYLIMIT    = "pricecheck/displaylimit";
constexpr auto PTA_CONFIG_CORRUPTOVERRIDE = "pricecheck/corruptoverride";
constexpr auto PTA_CONFIG_CORRUPTSEARCH   = "pricecheck/corruptsearch";

constexpr auto PTA_CONFIG_DEFAULT_DISPLAYLIMIT    = 12;
constexpr auto PTA_CONFIG_DEFAULT_CORRUPTOVERRIDE = false;
constexpr auto PTA_CONFIG_DEFAULT_CORRUPTSEARCH   = "Any";
#define PTA_CONFIG_DEFAULT_LOGLEVEL PTA_LOG_DEBUG
