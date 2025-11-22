#ifndef __TRANSPORT_SHM_NOTIFIER_BASE_H__
#define __TRANSPORT_SHM_NOTIFIER_BASE_H__

#include "transport/shm/readable_info.h"

namespace cyber{
namespace transport{

class NotifierBase;
using NotifierPtr = NotifierBase*;
class NotifierBase{
    
public:
    virtual ~NotifierBase() = default;

    virtual void Shutdown() = 0;
    virtual bool Notify(const ReadableInfo& info) = 0;
    virtual bool Listen(int timeout_ms, ReadableInfo* info) = 0;
}; 

} // namespace cyber
} // namespace transport

#endif