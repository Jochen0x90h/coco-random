#include "Random_RNG.hpp"
#include <coco/platform/platform.hpp>
#include <array>
#include <cstdint>


namespace coco {

Random_RNG::Random_RNG(Loop_RTC0 &loop) {
	NRF_RNG->INTENSET = N(RNG_INTENSET_VALRDY, Enabled);

	// add to list of handlers
	loop.handlers.add(*this);
}

Random_RNG::~Random_RNG() {
}

Awaitable<uint32_t *> Random_RNG::draw(uint32_t &value) {
	if (this->waitlist.empty()) {
		this->count = 0;
		NRF_RNG->TASKS_START = TRIGGER;
	}
	return {this->waitlist, &value};
}

uint32_t Random_RNG::drawBlocking() {
	uint32_t value = 0;
	NRF_RNG->TASKS_START = TRIGGER;
	for (int i = 0; i < 4; ++i) {
		while (!NRF_RNG->EVENTS_VALRDY);
		NRF_RNG->EVENTS_VALRDY = 0;
		value <<= 8;
		value |= NRF_RNG->VALUE;
	}
	
	// stop random number generator if no waiting coroutines
	if (this->waitlist.empty())
		NRF_RNG->TASKS_STOP = TRIGGER;
	
	return value;
}

void Random_RNG::handle() {
	if (NRF_RNG->EVENTS_VALRDY) {
		// clear pending interrupt flag at peripheral and NVIC
		NRF_RNG->EVENTS_VALRDY = 0;
		clearInterrupt(RNG_IRQn);

		// get new value
		this->value <<= 8;
		this->value |= NRF_RNG->VALUE;

		++this->count;
		if (this->count >= 4) {
			this->count = 0;

			// resume first waiting coroutine
			this->waitlist.resumeFirst([this](uint32_t *value) {
				*value = this->value;
				return true;
			});

			// stop random number generator if no more waiting coroutines
			if (this->waitlist.empty())
				NRF_RNG->TASKS_STOP = TRIGGER;
		}

	}
}

} // namespace coco
