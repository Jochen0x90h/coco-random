#pragma once

#include <coco/Coroutine.hpp>
#include <cstdint>


namespace coco {

/**
	Hardware random number generator interface (comparable to /dev/random) that generates random 32 bit values
	that can be used as seed for pseudo random number renerators.
	Can use a random number generator peripheral or the noise of an analog/digital converter.
*/
class Random {
public:

	virtual ~Random();

	/**
		Draw random 32 bit value
		@param value output random value
		@return use co_await on return value to await completion
	*/
	[[nodiscard]] virtual Awaitable<uint32_t *> draw(uint32_t &value) = 0;

	/**
		Draw random 32 bit value
		@return random value
	*/
	[[nodiscard]] virtual uint32_t drawBlocking() = 0;
};

} // namespace coco
