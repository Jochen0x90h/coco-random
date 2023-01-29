#include "Random_random.hpp"


namespace coco {

Random_random::~Random_random() {
}

Awaitable<uint32_t *> Random_random::draw(uint32_t &value) {
	value = this->device();
	return {};
}

uint32_t Random_random::drawBlocking() {
	return this->device();
}

} // namespace coco
