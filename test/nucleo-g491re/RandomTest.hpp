#pragma once

#include <coco/platform/Loop_TIM2.hpp>
#include <coco/platform/Random32_rng.hpp>
#include <coco/board/config.hpp>


using namespace coco;

// drivers for RandomTest
struct Drivers {
    Loop_TIM2 loop{APB1_TIMER_CLOCK};

    // random number generator
    Random32_rng random;
};

Drivers drivers;
