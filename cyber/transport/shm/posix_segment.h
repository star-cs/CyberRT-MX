

#ifndef __TRANSPORT_SHM_POSIX_SEGMENT_H__
#define __TRANSPORT_SHM_POSIX_SEGMENT_H__

#include <string>
#include "transport/shm/segment.h"

namespace cyber
{
namespace transport
{

    class PosixSegment : public Segment
    {
    public:
        explicit PosixSegment(uint64_t channel_id);
        virtual ~PosixSegment();

        static const char *Type() { return "posix"; }

    private:
        void Reset() override;
        bool Remove() override;
        bool OpenOnly() override;
        bool OpenOrCreate() override;

        std::string shm_name_;
    };

} // namespace transport
} // namespace cyber

#endif