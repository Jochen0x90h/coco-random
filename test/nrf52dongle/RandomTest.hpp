#pragma once

#include <coco/platform/Loop_RTC0.hpp>
#include <coco/platform/Random32_rng.hpp>


using namespace coco;

// drivers for RandomTest
struct Drivers {
    Loop_RTC0 loop;

    // random number generator
    Random32_rng random;
};

Drivers drivers;
