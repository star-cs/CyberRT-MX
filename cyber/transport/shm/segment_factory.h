#ifndef __TRANSPORT_SHM_SEGMENT_FACTORY_H__
#define __TRANSPORT_SHM_SEGMENT_FACTORY_H__

#include "transport/shm/segment.h"

namespace cyber
{
namespace transport
{

    class SegmentFactory
    {
    public:
        static SegmentPtr CreateSegment(uint64_t channel_id);
    };

} // namespace transport
} // namespace cyber

#endif