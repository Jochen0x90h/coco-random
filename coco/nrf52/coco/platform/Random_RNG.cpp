#include "Random_RNG.hpp"
#include <coco/platform/platform.hpp>


namespace coco {

Random_RNG::~Random_RNG() {
}

void Random_RNG::draw(void *data, int size) {
	NRF_RNG->TASKS_START = TRIGGER;

	uint8_t *dst = reinterpret_cast<uint8_t *>(data);
	for (int i = 0; i < size; ++i) {
		// wait until a random value is ready
		while (!NRF_RNG->EVENTS_VALRDY);
		NRF_RNG->EVENTS_VALRDY = 0;
		dst[i] = NRF_RNG->VALUE;
	}

	NRF_RNG->TASKS_STOP = TRIGGER;
}

} // namespace coco
