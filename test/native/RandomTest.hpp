#pragma once

#include <coco/platform/Loop_native.hpp>
#include <coco/platform/Random_random.hpp>
#include <coco/platform/UsbDevice_cout.hpp>


using namespace coco;

// drivers for RandomTest
struct Drivers {
	Loop_native loop;
	Random_random random;
	UsbDevice_cout device{loop};
	UsbDevice_cout::ControlBuffer<256> controlBuffer{device};
	UsbDevice_cout::BulkEndpoint endpoint1{device, 1};
	UsbDevice_cout::BulkEndpoint endpoint2{device, 2};
	UsbDevice_cout::BulkBuffer<129> buffer1{endpoint1};
	UsbDevice_cout::BulkBuffer<129> buffer2{endpoint2};
};
