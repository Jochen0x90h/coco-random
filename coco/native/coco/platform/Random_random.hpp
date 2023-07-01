#pragma once

#include <coco/BufferImpl.hpp>
#include <random>


namespace coco {

/**
	Blocking implementation of the Random interface using std::random_device.
	Use only for obtaining a seed for a pseudo random number generator.
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
