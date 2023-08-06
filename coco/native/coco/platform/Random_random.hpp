#pragma once

#include <coco/BufferImpl.hpp>
#include <random>


namespace coco {

/**
	Blocking implementation of a random number generator using std::random_device.
	Recommended is to only obtain a seed for a pseudo random number generator.
*/
namespace Random_random {

	class Buffer : public BufferImpl {
	public:

		Buffer(int size);
		~Buffer() override;

		bool startInternal(int size, Op op) override;
		void cancel() override;

	protected:

		// random device (on linux probably based on /dev/random)
		std::random_device device;
	};
}

} // namespace coco
