#include "Random_random.hpp"


namespace coco {

Random_random::~Random_random() {
}

uint32_t Random_random::get() {
    return device_();
}

} // namespace coco
