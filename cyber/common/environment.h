#ifndef __COMMON_ENVIRONMENT_H__
#define __COMMON_ENVIRONMENT_H__

#include <string>
#include <iostream>
#include "common/log.h"
namespace cyber
{
namespace common
{

    /**
     * @brief  获取环境变量
     */
    inline std::string GetEnv(const std::string &var_name, const std::string &default_value = "")
    {
        const char *var = std::getenv(var_name.c_str());
        if (var == nullptr) {
            AWARN << "Environment variable [" << var_name << "] not set, fallback to "
                  << default_value;
            return default_value;
        }
        return std::string(var);
    }

    /**
     * @brief  设置工作空间路径
     */
    inline const std::string WorkRoot()
    {
        std::string work_root = GetEnv("CMW_PATH");
        if (work_root.empty()) {
            work_root = "/cmw";
        }
        return work_root;
    }

} // namespace common
} // namespace cyber

#endif