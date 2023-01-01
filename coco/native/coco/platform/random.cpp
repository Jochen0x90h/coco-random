#include <coco/random.hpp>
#include <random>


namespace coco {


namespace random {

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<uint64_t> dist;

void init() {
}

uint8_t u8() {
	return random::dist(random::mt);
}

uint16_t u16() {
	return random::dist(random::mt);
}

uint32_t u32() {
	return random::dist(random::mt);
}

uint64_t u64() {
	return random::dist(random::mt);
}

} // namespace random
} // namespace coco
