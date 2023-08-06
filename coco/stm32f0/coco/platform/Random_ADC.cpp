#include "Random_ADC.hpp"
#include <coco/platform/platform.hpp>


namespace coco {

bool Random_RNG::BufferBase::startInternal(int size, Op op) {
	// check if READ flag is set
	assert((op & Op::READ) != 0);

	// todo
	// see https://www.mikrocontroller.net/topic/358453

	setReady(size);
	return true;
}

void Random_RNG::BufferBase::cancel() {
}

} // namespace coco
