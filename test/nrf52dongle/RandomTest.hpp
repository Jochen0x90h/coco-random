#pragma once

#include <coco/platform/Loop_RTC0.hpp>
#include <coco/platform/Random_RNG.hpp>
#include <coco/platform/UsbDevice_USBD.hpp>


using namespace coco;

// drivers for RandomTest
struct Drivers {
	Loop_RTC0 loop;
	Random_RNG::Buffer<128> random;
	UsbDevice_USBD device{loop};
	UsbDevice_USBD::ControlBuffer<256> controlBuffer{device};
	UsbDevice_USBD::BulkEndpoint endpoint1{device, 1};
	UsbDevice_USBD::BulkBuffer<129> usb1{endpoint1};
	UsbDevice_USBD::BulkEndpoint endpoint2{device, 2};
	UsbDevice_USBD::BulkBuffer<129> usb2{endpoint2};
};
