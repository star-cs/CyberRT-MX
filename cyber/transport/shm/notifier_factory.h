#ifndef __TRANSPORT_SHM_NOTIFIER_FACTORY_H__
#define __TRANSPORT_SHM_NOTIFIER_FACTORY_H__


#include <memory>
#include "transport/shm/notifier_base.h"


namespace cyber{
namespace transport{


class NotifierFactory{
    public:
        static NotifierPtr CreateNotifier();
    private:
        static NotifierPtr CreateConditionNotifier();
        static NotifierPtr CreateMulticastNotifier();
};


}
}



#endif