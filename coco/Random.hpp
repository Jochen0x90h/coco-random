#pragma once

#include <cstdint>


namespace coco {

/// @brief Hardware random number generator interface (comparable to /dev/random).
/// Blocks until a random number is available. To optimize speed, use as seed for a pseudo random number generator.
class Random {
public:

    virtual ~Random() {}

    /// @brief Get a random value.
    /// Blocks execution until a random value is generated.
    /// Dependent on the implementation, the value may be only 8 or 16 bits wide.
    /// @return A random integer value
    virtual uint32_t get() = 0;
};

} // namespace coco
