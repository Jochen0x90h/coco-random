#include "Random_RNG.hpp"
#include <coco/platform/platform.hpp>
//#include <array>
//#include <cstdint>


namespace coco {

bool Random_RNG::BufferBase::startInternal(int size, Op op) {
	// check if READ flag is set
	assert((op & Op::READ) != 0);

	NRF_RNG->TASKS_START = TRIGGER;

	auto data = this->dat;
	for (int i = 0; i < size; ++i) {
		while (!NRF_RNG->EVENTS_VALRDY);
		NRF_RNG->EVENTS_VALRDY = 0;
		data[i] = NRF_RNG->VALUE;
	}

	NRF_RNG->TASKS_STOP = TRIGGER;

	setReady(size);
	return true;
}

void Random_RNG::BufferBase::cancel() {
}

} // namespace coco
