#include <coco/loop.hpp>
#include <coco/Buffer.hpp>
#include <coco/String.hpp>
#include <RandomTestHost.hpp>
#include <iostream>
#include <iomanip>


// Host for UsbDeviceTest
// Flash UsbDeviceTest onto the device, then run this


using namespace coco;

std::ostream &operator <<(std::ostream &s, String v) {
	return s << std::string(v.data(), v.size());
}

struct str {
	str(const char *s) : s(s) {}
	str(const unsigned char *s) : s((const char *)s) {}
	const char *s;
};
std::ostream &operator <<(std::ostream &s, str v) {
	return s << v.s;
}

struct dec {
	dec(int i) : i(i) {}
	int i;
};
std::ostream &operator <<(std::ostream &s, dec v) {
	return s << std::dec << v.i;
}

struct hex {
	hex(uint8_t v) : w(2), v(v) {}
	hex(uint16_t v) : w(4), v(v) {}
	int w;
	unsigned int v;
};
std::ostream &operator <<(std::ostream &s, hex h) {
	return s << std::setfill('0') << std::setw(h.w) << std::hex << h.v;
}

Coroutine handler(UsbHostDevice &device, Stream &stream, int endpoint) {
	Buffer<uint8_t, 32> buffer;

	while (true) {
		// wait until device is connected
		std::cout << "wait for device to be connected" << std::endl;
		co_await device.targetState(UsbHostDevice::State::CONNECTED);

		std::cout << "read random data" << std::endl;
		while (device.isConnected()) {
			// receive from device
			co_await stream.read(buffer);

			std::cout << endpoint << ": ";
			for (int i = 0; i < buffer.size(); ++i) {
				if (i > 0)
					std::cout << ", ";
				std::cout << hex(buffer[i])	;			
			}
			std::cout << std::endl;
		}
	}
}

int main() {
	Drivers drivers;

	handler(drivers.device, drivers.endpoint1, 1);
	handler(drivers.device, drivers.endpoint2, 2);

	drivers.loop.run();

	return 0;
}
