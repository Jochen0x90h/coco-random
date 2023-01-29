#pragma once

#include <coco/platform/Loop_RTC0.hpp>
#include <coco/platform/Random_RNG.hpp>
#include <coco/platform/UsbDevice_USBD.hpp>


using namespace coco;

// drivers for RandomTest
struct Drivers {
	Loop_RTC0 loop;
	Random_RNG random{loop};
	UsbDevice_USBD device{loop};
	UsbDevice_USBD::BulkEndpoint endpoint1{device, 1};
	UsbDevice_USBD::BulkEndpoint endpoint2{device, 2};
};
