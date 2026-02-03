#pragma once

#include <coco/Random.hpp>
#if !(defined(STM32F0) || defined(STM32C0) || defined(STM32F3))
#include <coco/platform/rng.hpp>
#endif


#if defined(HAVE_RNG) || defined(NRF_RNG)
namespace coco {

/// @brief Implementation of the Random interface for 32 bit random numbers using the hardware random number generator HAL.
///
/// Resources:
///   nrf52
///     NRF_RNG
///   stm32
///     RNG
class Random32_rng : public Random {
public:
    Random32_rng();
    ~Random32_rng() override;

    uint32_t get() override;

protected:
    rng::Instance rng_;
};

} // namespace coco
#endif // HAVE_RNG
