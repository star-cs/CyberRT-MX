#include "transport/shm/state.h"

namespace cyber{
namespace transport{

State::State(const uint64_t& ceiling_msg_size)
    : ceiling_msg_size_(ceiling_msg_size) {}

State::~State() {}
}
}