#pragma once

#include <coco/BufferImpl.hpp>


namespace coco {

/**
	Blocking implementation of a random number generator using the temperature sensor connected to the ADC.
	Recommended is to only obtain a seed for a pseudo random number generator.

	Resources:
		ADC
*/
namespace Random_RNG {

	class BufferBase : public BufferImpl {
	public:
		/**
			Constructor
		*/
		BufferBase(uint8_t *data, int capacity) : BufferImpl(0, data, capacity, Buffer::State::READY) {}

		bool start(Op op) override;
		bool cancel() override;
	};

	/**
		Buffer for reading from the random number generator.
		@tparam N size of buffer
	*/
	template <int N>
	class Buffer : public BufferBase {
	public:
		Buffer() : BufferBase(data, N) {}

	protected:
		alignas(4) uint8_t data[N];
	};
}

} // namespace coco
