#ifndef __TRANSPORT_SHM_XSI_SEGMENT_H__
#define __TRANSPORT_SHM_XSI_SEGMENT_H__

#include "transport/shm/segment.h"

namespace cyber
{
namespace transport
{

    class XsiSegment : public Segment
    {

    public:
        explicit XsiSegment(uint64_t channel_id);
        virtual ~XsiSegment();

        static const char *Type() { return "xsi"; }

    private:
        void Reset() override;
        bool Remove() override;
        bool OpenOnly() override;
        bool OpenOrCreate() override;

        key_t key_;
    };

} // namespace transport
} // namespace cyber

#endif