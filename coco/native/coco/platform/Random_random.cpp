#include "Random_random.hpp"


namespace coco {

Random_random::~Random_random() {
}

void Random_random::draw(void *data, int size) {
	uint32_t r;
	int x = 0;
	uint8_t *dst = reinterpret_cast<uint8_t *>(data);
	for (int i = 0; i < size; ++i) {
		if (x == 0) {
			// draw 32bit random number
			r = this->device();
			x = 4;
		}

		dst[i] = r;
		r >>= 8;
		--x;
	}
}

} // namespace coco
