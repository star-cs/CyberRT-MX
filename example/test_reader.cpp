#include "common/global_data.h"
#include "config/role_attributes.h"
#include "transport/dispatcher/rtps_dispatcher.h"
#include "common/util.h"
#include "transport/receiver/receiver.h"
#include "transport/transport.h"
#include "config/topology_change.h"
#include "config/transport_config.h"
#include <string>
#include <cstring>

using namespace cyber::transport;
using namespace cyber::common;
using namespace cyber::config;

using ReceiverPtr = std::shared_ptr<Receiver<std::string>>;

void TEST_GLOBAL_DATA()
{
    std::cout << "--------------------------Global_Data Test--------------------------"
              << std::endl;
    std::cout << "HostIP: " << GlobalData::Instance()->HostIp() << std::endl;
    std::cout << "HostName: " << GlobalData::Instance()->HostName() << std::endl;
    std::cout << "ProcessId: " << GlobalData::Instance()->ProcessId() << std::endl;
    std::cout << "ProcessGroup: " << GlobalData::Instance()->ProcessGroup() << std::endl;
}

void TEST_MUTILISTENER(OptionalMode mode)
{
    auto dispatcher = RtpsDispatcher::Instance();
    RoleAttributes attr;
    attr.channel_name = "exampleTopic1";
    attr.host_name = GlobalData::Instance()->HostName();
    attr.host_ip = GlobalData::Instance()->HostIp();
    attr.process_id = GlobalData::Instance()->ProcessId();
    attr.channel_id = GlobalData::Instance()->RegisterChannel(attr.channel_name);
    QosProfile qos;
    attr.qos_profile = qos;

    const char* mode_str = (mode == OptionalMode::SHM) ? "SHM" : "RTPS";
    std::cout << "Using transport mode: " << mode_str << std::endl;

    auto listener1 = [](const std::shared_ptr<std::string> &message, const MessageInfo &info,
                        const RoleAttributes &) {
        std::cout << *message << " data1"
                  << " seq: " << info.seq_num() << std::endl;
    };
    auto listener2 = [](const std::shared_ptr<std::string> &message, const MessageInfo &,
                        const RoleAttributes &) { std::cout << *message << " data2" << std::endl; };
    ReceiverPtr receiver1 = Transport::Instance()->CreateReceiver<std::string>(attr, listener1, mode);

    ReceiverPtr receiver2 = Transport::Instance()->CreateReceiver<std::string>(attr, listener2, mode);

    printf("Press Enter to stop the Reader.\n");
    std::cin.ignore();
}

void TEST_ChangeMsg(OptionalMode mode)
{
    RoleAttributes attr;
    attr.channel_name = "exampleTopic2";
    attr.host_name = GlobalData::Instance()->HostName();
    attr.host_ip = GlobalData::Instance()->HostIp();
    attr.process_id = GlobalData::Instance()->ProcessId();
    attr.channel_id = GlobalData::Instance()->RegisterChannel(attr.channel_name);
    QosProfile qos;
    attr.qos_profile = qos;
    
    const char* mode_str = (mode == OptionalMode::SHM) ? "SHM" : "RTPS";
    std::cout << "Using transport mode: " << mode_str << std::endl;
    
    auto listener1 = [](const std::shared_ptr<ChangeMsg> &message, const MessageInfo &info,
                        const RoleAttributes &) {
        std::cout << "time: " << message->timestamp << "operate_type:" << message->operate_type
                  << "seq:" << info.seq_num() << std::endl;
    };
    auto receiver1 = Transport::Instance()->CreateReceiver<ChangeMsg>(attr, listener1, mode);
    printf("Press Enter to stop the Reader.\n");
    std::cin.ignore();
}

void PrintUsage(const char* program_name)
{
    std::cout << "Usage: " << program_name << " [OPTIONS]\n"
              << "Options:\n"
              << "  -m, --mode MODE    Transport mode: rtps or shm (default: rtps)\n"
              << "  -h, --help         Show this help message\n"
              << "\n"
              << "Examples:\n"
              << "  " << program_name << " --mode rtps    # Use RTPS transport\n"
              << "  " << program_name << " --mode shm     # Use Shared Memory transport\n"
              << std::endl;
}

int main(int argc, char **argv)
{
    OptionalMode mode = OptionalMode::RTPS; // 默认使用 RTPS
    
    // 解析命令行参数
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            PrintUsage(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--mode") == 0) {
            if (i + 1 < argc) {
                std::string mode_str = argv[i + 1];
                if (mode_str == "shm" || mode_str == "SHM") {
                    mode = OptionalMode::SHM;
                } else if (mode_str == "rtps" || mode_str == "RTPS") {
                    mode = OptionalMode::RTPS;
                } else {
                    std::cerr << "Error: Invalid mode '" << mode_str 
                              << "'. Use 'rtps' or 'shm'." << std::endl;
                    PrintUsage(argv[0]);
                    return 1;
                }
                i++; // 跳过已处理的参数值
            } else {
                std::cerr << "Error: --mode requires a value (rtps or shm)" << std::endl;
                PrintUsage(argv[0]);
                return 1;
            }
        } else {
            std::cerr << "Error: Unknown option '" << argv[i] << "'" << std::endl;
            PrintUsage(argv[0]);
            return 1;
        }
    }
    
    Logger_Init("reader.log");
    TEST_GLOBAL_DATA();
    TEST_MUTILISTENER(mode);
    // TEST_ChangeMsg(mode);
    return 0;
}
