#pragma once

#include <coco/platform/Loop_native.hpp>
#include <coco/platform/Random_random.hpp>
#include <coco/platform/UsbDevice_cout.hpp>


using namespace coco;

// drivers for RandomTest
struct Drivers {
	Loop_native loop;

	// random number generator
	Random_random random;

	// usb device
	UsbDevice_cout device{loop};
	UsbDevice_cout::ControlBuffer controlBuffer{128, device};
	UsbDevice_cout::Endpoint endpoint1{device, 1};
	UsbDevice_cout::Endpoint endpoint2{device, 2};
	UsbDevice_cout::Buffer usb1{129, endpoint1};
	UsbDevice_cout::Buffer usb2{129, endpoint2};
};

Drivers drivers;
