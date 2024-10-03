#pragma once

#include <coco/Random.hpp>
#include <random>


namespace coco {

/**
	Blocking implementation of a random number generator using std::random_device.
*/
class Random_random : public Random {
public:
	~Random_random() override;

	void draw(void *data, int size) override;

protected:
	// random device (on linux probably based on /dev/random)
	std::random_device device;
};

} // namespace coco
