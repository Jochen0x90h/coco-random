#pragma once

#include <coco/Random.hpp>


namespace coco {

/**
	implementation of a random number generator using the hardware random number generator.
	Recommended is to only obtain a seed for a pseudo random number generator.

	Reference Manual:
		https://infocenter.nordicsemi.com/topic/ps_nrf52840/rng.html?cp=5_0_0_5_20

	Resources:
		NRF_RNG
*/
class Random_RNG : public Random {
public:
	~Random_RNG() override;

	void draw(void *data, int size) override;
};

} // namespace coco
