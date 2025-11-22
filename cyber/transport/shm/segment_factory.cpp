#include "transport/shm/segment_factory.h"
#include "common/global_data.h"
#include "transport/shm/xsi_segment.h"
#include "common/log.h"
#include "transport/shm/posix_segment.h"
namespace cyber
{
namespace transport
{

    // using cyber::common::GlobalData;

    auto SegmentFactory::CreateSegment(uint64_t channel_id) -> SegmentPtr
    {
        std::string segment_type(XsiSegment::Type());

        ADEBUG << "segment type: " << segment_type;
        if (segment_type == PosixSegment::Type()) {
            return std::make_shared<PosixSegment>(channel_id);
        }
        return std::make_shared<XsiSegment>(channel_id);
    }

} // namespace transport
} // namespace cyber