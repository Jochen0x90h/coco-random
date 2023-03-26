#pragma once

#include <coco/Random.hpp>
#include <coco/platform/Loop_RTC0.hpp>


namespace coco {

/**
	Implementatoin of the Random interface using the hardware random number generator.
	https://infocenter.nordicsemi.com/index.jsp?topic=%2Fps_nrf52840%2Frng.html&cp=4_0_0_5_20

	Resources:
		NRF_RNG
*/
class Random_RNG : public Random, public Loop_RTC0::Handler {
public:

	Random_RNG(Loop_RTC0 &loop);
	~Random_RNG() override;

	[[nodiscard]] Awaitable<uint32_t *> draw(uint32_t &value) override;
	[[nodiscard]] uint32_t drawBlocking() override;

protected:

	void handle() override;

	int count;
	uint32_t value;

	// waiting coroutines
	TaskList<uint32_t *> tasks;
};

} // namespace coco
