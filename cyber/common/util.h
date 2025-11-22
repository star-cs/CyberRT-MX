#ifndef __COMMON_UTIL_H__
#define __COMMON_UTIL_H__

#include <string>
#include <type_traits>

namespace cyber
{
namespace common
{

    /*
      std::hash<std::string>{} ： 创建一个 std::hash<std::string>的临时对象 { } 是初始化列表 ，
      std::hash<std::string> 内部重载了() 获取一个字符串的哈希值
    */
    inline std::size_t Hash(const std::string &key)
    {
        return std::hash<std::string>{}(key);
    }

} // namespace common
} // namespace cyber

#endif