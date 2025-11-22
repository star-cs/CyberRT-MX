#ifndef __TRANSPORT_RTPS_PARTICIPANT_H__
#define __TRANSPORT_RTPS_PARTICIPANT_H__
#include <string>
#include <fastdds/rtps/participant/RTPSParticipant.h>
#include <atomic>
#include <memory>
#include <mutex>
namespace cyber
{
namespace transport
{
    class Participant;
    using ParticipantPtr = std::shared_ptr<Participant>;

    class Participant
    {
    public:
        Participant(const std::string &name, int send_port,
                    eprosima::fastrtps::rtps::RTPSParticipantListener *listener = nullptr);
        virtual ~Participant();

        void Shutdown();
        bool is_shutdown() const { return shutdown_.load(); }

        //返回rtps的Participant
        eprosima::fastrtps::rtps::RTPSParticipant *fastrtps_participant();

    private:
        //创建一个 rtps的Participant
        void CreateFastRtpsParticipant(const std::string &name, int send_port,
                                       eprosima::fastrtps::rtps::RTPSParticipantListener *listener);

        std::atomic<bool> shutdown_;
        std::string name_; // RTPSParticipant name
        int send_port_;
        eprosima::fastrtps::rtps::RTPSParticipant *fastrtps_participant_; // RTPSParticipant
        eprosima::fastrtps::rtps::RTPSParticipantListener *listener_;     // RTPSParticipantListener
        std::mutex mutex_;
    };

} // namespace transport
} // namespace cyber

#endif