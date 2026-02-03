#include <RandomTest.hpp>
#include <coco/convert.hpp>
#include <coco/debug.hpp>


/*
    Random number generator test
    Prints random numbers to debug::out
*/

using namespace coco;


// generate random numbers
Coroutine generate(Loop &loop, Random &random) {
    while (true) {
        // generate random number
        uint32_t value = random.get();

        debug::out << hex(value) << '\n';

        co_await loop.sleep(100ms);
    }
}

int main() {
    debug::set(debug::GREEN);
    debug::out << "RandomTest\n";

    generate(drivers.loop, drivers.random);

    drivers.loop.run();
}
