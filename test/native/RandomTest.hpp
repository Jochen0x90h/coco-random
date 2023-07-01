#pragma once

#include <coco/platform/Loop_native.hpp>
#include <coco/platform/Random_random.hpp>
#include <coco/platform/UsbDevice_cout.hpp>


using namespace coco;

// drivers for RandomTest
struct Drivers {
	Loop_native loop;
	Random_random::Buffer random{256};
	UsbDevice_cout device{loop};
	UsbDevice_cout::ControlBuffer controlBuffer{device, 32};
	UsbDevice_cout::BulkEndpoint endpoint1{device, 1};
	UsbDevice_cout::BulkBuffer usb1{endpoint1, 129};
	UsbDevice_cout::BulkEndpoint endpoint2{device, 2};
	UsbDevice_cout::BulkBuffer usb2{endpoint2, 129};
};
