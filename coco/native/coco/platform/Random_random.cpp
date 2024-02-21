#include "Random_random.hpp"
#include <coco/align.hpp>


namespace coco {

Random_random::Buffer::Buffer(int size)
	: BufferImpl(new uint8_t[align4(size)], size, State::READY)
{
}

Random_random::Buffer::~Buffer() {
	delete [] this->p.data;
}

bool Random_random::Buffer::start(Op op) {
	// check if READ flag is set
	assert((op & Op::READ) != 0);

	int n = (this->p.size + 3) / 4;
	auto data = reinterpret_cast<uint32_t *>(this->p.data);
	for (int i = 0; i < n; ++i) {
		data[i] = this->device();
	}

	setReady();
	return true;
}

bool Random_random::Buffer::cancel() {
	return true;
}

} // namespace coco
