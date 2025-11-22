#ifndef __CONFIG_CLASSICCONF_H__
#define __CONFIG_CLASSICCONF_H__

#include <string>
#include <vector>

namespace cyber
{
namespace config
{
    struct ClassicTask {
        std::string name;
        uint32_t prio = 0; // 默认值
        std::string group_name;
    };

    struct SchedGroup {
        std::string name;
        uint32_t processor_num = 0; // 默认值
        std::string affinity;
        std::string cpuset;
        std::string processor_policy;
        int32_t processor_prio = 0; // 默认值
        std::vector<ClassicTask> tasks;
    };

    struct ClassicConf {
        std::vector<SchedGroup> groups;
    };

} // namespace config
} // namespace cyber

#endif