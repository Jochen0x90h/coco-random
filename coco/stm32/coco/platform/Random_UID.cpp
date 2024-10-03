#include "Random_UID.hpp"
#include <coco/platform/platform.hpp>


namespace coco {

Random_UID::~Random_UID() {
}

void Random_UID::draw(void *data, int size) {
	// use UID as random source
	// other idea: https://www.mikrocontroller.net/topic/358453
	const uint8_t *UID = (const uint8_t *)UID_BASE;

	uint8_t *dst = reinterpret_cast<uint8_t *>(data);
	int x = this->x;
	for (int i = 0; i < size; ++i) {
		dst[i] = UID[x];

		++x;
		if (x == 12)
			x = 0;
	}
	this->x = x;
}

} // namespace coco
