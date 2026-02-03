#include "Random32_rng.hpp"
#include <coco/debug.hpp>


#if defined(HAVE_RNG) || defined(NRF_RNG)
namespace coco {

Random32_rng::Random32_rng() {
#ifdef HAVE_RNG_ENABLE_CLOCK
    rng_ = rng::enableClock()
#else
    rng_ = rng::instance()
#endif
        .configure(rng::Config::DEFAULT);
}

Random32_rng::~Random32_rng() {
}

uint32_t Random32_rng::get() {
    rng_.start();
    uint32_t value;
    if constexpr (sizeof(rng::Value) >= 4) {
        value = rng_.waitValue();
    } else {
        value = 0;
        for (unsigned int i = 0; i < 4 / sizeof(rng::Value); ++i) {
            value = (value << sizeof(rng::Value) * 8) | rng_.waitValue();
        }
    }
    rng_.stop();
    return value;
}

} // namespace coco
#endif // HAVE_RNG
