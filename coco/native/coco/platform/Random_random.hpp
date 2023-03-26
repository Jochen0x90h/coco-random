#pragma once

#include <coco/Random.hpp>
#include <random>


namespace coco {

/**
	Implementatoin of the Random interface using c++ std::random_device
*/
class Random_random : public Random {
public:

	Random_random() {}
	~Random_random() override;

	[[nodiscard]] Awaitable<uint32_t *> draw(uint32_t &value) override;
	[[nodiscard]] uint32_t drawBlocking() override;

protected:

	// random device (e.g. dev/random)
	std::random_device device;
};

} // namespace coco
