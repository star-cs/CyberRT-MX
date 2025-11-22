#ifndef __COMMON_CONFPARSE_H__
#define __COMMON_CONFPARSE_H__

#include <string>
#include "config/cmw_conf.h"

namespace cyber
{
namespace config
{

    bool GetCyberConfFromFile(const std::string &file_path, CmwConfig *config);
}
} // namespace cyber

#endif