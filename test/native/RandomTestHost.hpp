#pragma once

#include <coco/platform/Loop_native.hpp>
#include <coco/platform/UsbHost_native.hpp>


using namespace coco;

// drivers of USB host for RandomTest
struct Drivers {
	Loop_native loop;
	UsbHost_native host{loop};
    UsbHost_native::Device device{host, [](const usb::DeviceDescriptor &deviceDescriptor) {
		return deviceDescriptor.idVendor == 0x1915 && deviceDescriptor.idProduct == 0x1337;
	}};
	UsbHost_native::ControlBuffer controlBuffer{32, device};
	UsbHost_native::Endpoint endpoint1{device, 1};
	UsbHost_native::Endpoint endpoint2{device, 2};
	UsbHost_native::Buffer buffer1{129, endpoint1};
	UsbHost_native::Buffer buffer2{129, endpoint2};
};

Drivers drivers;
