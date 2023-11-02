#include "Random_ADC.hpp"
#include <coco/platform/platform.hpp>


namespace coco {

bool Random_RNG::BufferBase::start(Op op) {
	// check if READ flag is set
	assert((op & Op::READ) != 0);

	// todo
	// see https://www.mikrocontroller.net/topic/358453

	setReady();
	return true;
}

bool Random_RNG::BufferBase::cancel() {
	return true;
}

} // namespace coco
