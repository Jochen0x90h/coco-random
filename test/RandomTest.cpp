#include <RandomTest.hpp>
#include <coco/debug.hpp>
#include <coco/StreamOperators.hpp>


/*
	Random test
*/

using namespace coco;


// send random numbers to host
Coroutine generate(Loop &loop, Random &random) {
	while (true) {
		// generate random number
		uint8_t numbers[4];
		random.draw(numbers, 4);

		// print random numbers
		for (auto number : numbers)
			debug::out << dec(number) << ' ';
		debug::out << '\n';

		co_await loop.sleep(100ms);
	}
}

int main() {
	// start to send random numbers to host
	generate(drivers.loop, drivers.random);

	drivers.loop.run();
}
