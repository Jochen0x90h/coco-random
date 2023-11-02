#include "Random_RNG.hpp"
#include <coco/platform/platform.hpp>
//#include <array>
//#include <cstdint>


namespace coco {

bool Random_RNG::BufferBase::start(Op op) {
	// check if READ flag is set
	assert((op & Op::READ) != 0);

	NRF_RNG->TASKS_START = TRIGGER;

	auto data = this->p.data;
	int size = this->p.size;
	for (int i = 0; i < size; ++i) {
		while (!NRF_RNG->EVENTS_VALRDY);
		NRF_RNG->EVENTS_VALRDY = 0;
		data[i] = NRF_RNG->VALUE;
	}

	NRF_RNG->TASKS_STOP = TRIGGER;

	setReady();
	return true;
}

bool Random_RNG::BufferBase::cancel() {
	return true;
}

} // namespace coco
