#include <coco/random.hpp>
#include <coco/platform/platform.hpp>
#include <coco/assert.hpp>
#include <array>
#include <cstdint>


namespace coco {

/*
	Implementation of random number generator nRF52

	Resources:
		NRF_RNG
*/
namespace random {

uint8_t queue[16] __attribute__((aligned(4)));
volatile int readIndex;
volatile int writeIndex;

void init() {
	// does not matter if init() gets called multiple times

	random::readIndex = std::size(queue);
	random::writeIndex = 0;
	NRF_RNG->INTENSET = N(RNG_INTENSET_VALRDY, Enabled);
	enableInterrupt(RNG_IRQn);

	// immediately start to generate the first random numbers
	NRF_RNG->TASKS_START = TRIGGER;
}

extern "C" {
	void RNG_IRQHandler(void);
}

void RNG_IRQHandler(void) {
	if (NRF_RNG->EVENTS_VALRDY) {
		// new value is ready: clear pending interrupt flag at peripheral
		NRF_RNG->EVENTS_VALRDY = 0;
	
		int r = random::readIndex;
		int w = random::writeIndex;
		if (r - w > std::ssize(queue))
			w = r - std::size(queue);
		
		queue[w & (std::size(queue) - 1)] = NRF_RNG->VALUE;
		
		++w;
		
		// check if we catched up with the read plugIndex
		if (r - w <= 0)
			NRF_RNG->TASKS_STOP = TRIGGER;
			
		random::writeIndex = w;
	}	
}

uint8_t u8() {
	// assert that random number generator was initialized
	assert(NRF_RNG->INTENSET == N(RNG_INTENSET_VALRDY, Enabled));

	int index = random::readIndex;
	random::readIndex = index + 1;
	uint8_t value = queue[index & (std::size(queue) - 1)];
	NRF_RNG->TASKS_START = TRIGGER;
	return value;
}

uint16_t u16() {
	// assert that random number generator was initialized
	assert(NRF_RNG->INTENSET == N(RNG_INTENSET_VALRDY, Enabled));

	int index = (random::readIndex + 1) & ~1;
	random::readIndex = index + 2;
	uint16_t value = *(uint16_t*)&queue[index & (std::size(queue) - 1)];
	NRF_RNG->TASKS_START = TRIGGER;
	return value;
}

uint32_t u32() {
	// assert that random number generator was initialized
	assert(NRF_RNG->INTENSET == N(RNG_INTENSET_VALRDY, Enabled));

	int index = (random::readIndex + 3) & ~3;
	random::readIndex = index + 4;
	uint32_t value = *(uint32_t*)&queue[index & (std::size(queue) - 1)];
	NRF_RNG->TASKS_START = TRIGGER;
	return value;
}

uint64_t u64() {
	// assert that random number generator was initialized
	assert(NRF_RNG->INTENSET == N(RNG_INTENSET_VALRDY, Enabled));

	int index = (random::readIndex + 7) & ~7;
	random::readIndex = index + 8;
	uint64_t value = *(uint64_t*)&queue[index & (std::size(queue) - 1)];
	NRF_RNG->TASKS_START = TRIGGER;
	return value;
}

} // namespace random
} // namespace coco
