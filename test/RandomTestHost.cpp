#include <coco/String.hpp>
#include <coco/usb.hpp>
#include "libusb.hpp"
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
	hex(uint8_t i) : w(2), i(i) {}
	hex(uint16_t i) : w(4), i(i) {}
	int w;
	int i;
};
std::ostream &operator <<(std::ostream &s, hex v) {
	return s << std::setfill('0') << std::setw(v.w) << std::hex << v.i;
}

/*
// sent vendor specific control request to usb device
int controlOut(libusb_device_handle *handle, Request request, uint16_t wValue, uint16_t wIndex) {
	return libusb_control_transfer(handle,
		uint8_t(usb::Request::VENDOR_DEVICE_OUT),
		uint8_t(request),
		wValue,
		wIndex,
		nullptr,
		0,
		1000);
}*/

// print test status
void printStatus(const char *message, bool status) {
	std::cout << str(message) << ": " << (status ? "ok" : "error") << std::endl;
}

int main() {
	int r = libusb_init(nullptr);
	if (r < 0)
		return r;

	// get device list
	libusb_device **devices;
	ssize_t cnt = libusb_get_device_list(nullptr, &devices);
	if (cnt < 0) {
		libusb_exit(nullptr);
		return (int) cnt;
	}

	// iterate over devices
	for (int deviceIndex = 0; devices[deviceIndex]; ++deviceIndex) {
		libusb_device *dev = devices[deviceIndex];

		// get device descriptor
		libusb_device_descriptor desc;
		int ret = libusb_get_device_descriptor(dev, &desc);
		if (ret != LIBUSB_SUCCESS) {
			std::cerr << "get device descriptor error: " << dec(ret) << std::endl;
			continue;
		}
		
		// check vendor/product
		if (desc.idVendor != 0x1915 && desc.idProduct != 0x1337)
			continue;

		// print device
		//printDevice(devs[i]);

		// protocol: 0: binary, 1: text
		bool text = desc.bDeviceProtocol == 1;

		// open device
		libusb_device_handle *handle;
		ret = libusb_open(dev, &handle);
		if (ret != LIBUSB_SUCCESS) {
			std::cerr << "open error: " << dec(ret) << std::endl;
			continue;
		}

		if (libusb_kernel_driver_active(handle, 0) == 1) {
			std::cout << "detach active kernel driver" << std::endl;
			ret = libusb_detach_kernel_driver(handle, 0);
			if (ret != LIBUSB_SUCCESS) {
				std::cout << "detach kernel driver error: " << dec(ret) << std::endl;
				continue;
			}
		}
			
		// set configuration (reset alt_setting, reset toggles)
		ret = libusb_set_configuration(handle, 1);
		if (ret != LIBUSB_SUCCESS) {
			std::cerr << "set configuration error: " << dec(ret) << std::endl;
			continue;
		}

		// claim interface with bInterfaceNumber = 0
		ret = libusb_claim_interface(handle, 0);
		if (ret != LIBUSB_SUCCESS) {
			std::cerr << "claim interface error: " << dec(ret) << std::endl;
			continue;
		}

		//ret = libusb_set_interface_alt_setting(handle, 0, 0);
		//std::cout << "set alternate setting " << dec(ret) << std::endl;

		uint8_t buffer[32];

		// echo loop: send data to device and check if we get back the same data
		int sendLength = 128;
		bool allOk = true;
		for (int iter = 0; iter < 10000000; ++iter) {

			// receive from device
			int transferred;
			ret = libusb_bulk_transfer(handle, 1 | usb::IN, buffer, 16, &transferred, 10000);
			if (ret == LIBUSB_ERROR_TIMEOUT)
				std::cout << "receive timeout!" << std::endl;
			if (transferred != 16)
				std::cout << "wrong length received!" << std::endl;

			// wait
			//usleep(1000000);
		}
		libusb_close(handle);
		break;
	}

	libusb_free_device_list(devices, 1);
	libusb_exit(nullptr);
	return 0;
}
