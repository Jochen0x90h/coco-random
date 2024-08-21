#pragma once

#include <coco/platform/Loop_native.hpp>
#include <coco/platform/Random_random.hpp>


using namespace coco;

// drivers for RandomTest
struct Drivers {
	Loop_native loop;

	// random number generator
	Random_random random;
};

Drivers drivers;
