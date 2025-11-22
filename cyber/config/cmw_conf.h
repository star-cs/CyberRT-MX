#ifndef __CONFIG_CMWCONF_H__
#define __CONFIG_CMWCONF_H__

#include "config/scheduler_conf.h"
#include "config/transport_config.h"
#include <nlohmann/json.hpp>

namespace cyber
{
namespace config
{

    struct CmwConfig {
        SchedulerConf scheduler_conf;
        TransportConf transport_conf;
    };

    // nlohmann::json 序列化支持
    void from_json(const nlohmann::json &j, InnerThread &thread);
    void from_json(const nlohmann::json &j, ClassicTask &task);
    void from_json(const nlohmann::json &j, SchedGroup &group);
    void from_json(const nlohmann::json &j, ClassicConf &classic_conf);
    void from_json(const nlohmann::json &j, SchedulerConf &scheduler_conf);
    void from_json(const nlohmann::json &j, CmwConfig &cmw_config);

} // namespace config
} // namespace cyber

#endif