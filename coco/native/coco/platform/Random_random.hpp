#pragma once

#include <coco/Random.hpp>
#include <random>


namespace coco {

/// @brief Implementation of random number generator interface using std::random_device.
///
class Random_random : public Random {
public:
    ~Random_random() override;

    uint32_t get() override;

protected:
    // random device (on linux probably based on /dev/random)
    std::random_device device_;
};

} // namespace coco
