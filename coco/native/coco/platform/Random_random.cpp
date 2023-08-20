#include "Random_random.hpp"
#include <coco/align.hpp>


namespace coco {

Random_random::Buffer::Buffer(int size)
	: BufferImpl(new uint8_t[align4(size)], size, State::READY)
{
}

Random_random::Buffer::~Buffer() {
	delete [] this->dat;
}

bool Random_random::Buffer::startInternal(int size, Op op) {
	// check if READ flag is set
	assert((op & Op::READ) != 0);

	int n = (size + 3) / 4;
	auto data = reinterpret_cast<uint32_t *>(this->dat);
	for (int i = 0; i < n; ++i) {
		data[i] = this->device();
	}

	setReady(size);
	return true;
}

void Random_random::Buffer::cancel() {
}

} // namespace coco
