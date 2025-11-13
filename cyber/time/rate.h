#ifndef __TIME_RATE_H__
#define __TIME_RATE_H__

#include "time/time.h"
#include "time/duration.h"

namespace cyber
{

class Rate
{
public:
    explicit Rate(double frequency);
    explicit Rate(uint64_t nanoseconds);
    explicit Rate(const Duration &);
    void Sleep();
    void Reset();
    Duration CycleTime() const;
    Duration ExpectedCycleTime() const { return expected_cycle_time_; }

private:
    Time start_;
    Duration expected_cycle_time_;
    Duration actual_cycle_time_;
};

} // namespace cmw

#endif