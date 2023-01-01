#include <coco/loop.hpp>
#include <coco/debug.hpp>
#include <coco/board/UsbDevice.hpp>
#include <coco/random.hpp>


using namespace coco;

// device descriptor
static const usb::DeviceDescriptor deviceDescriptor = {
	.bLength = sizeof(usb::DeviceDescriptor),
	.bDescriptorType = usb::DescriptorType::DEVICE,
	.bcdUSB = 0x0200, // USB 2.0
	.bDeviceClass = 0xff, // no class
	.bDeviceSubClass = 0xff,
	.bDeviceProtocol = 0, // 0 = binary, 1 = text
	.bMaxPacketSize0 = 64, // max packet size for endpoint 0
	.idVendor = 0x1915, // Nordic Semiconductor
	.idProduct = 0x1337,
	.bcdDevice = 0x0100, // device version
	.iManufacturer = 0, // index into string table
	.iProduct = 0, // index into string table
	.iSerialNumber = 0, // index into string table
	.bNumConfigurations = 1
};

// configuration descriptor
struct UsbConfiguration {
	struct usb::ConfigDescriptor config;
	struct usb::InterfaceDescriptor interface;
	struct usb::EndpointDescriptor endpoints[1];
};

static const UsbConfiguration configurationDescriptor = {
	.config = {
		.bLength = sizeof(usb::ConfigDescriptor),
		.bDescriptorType = usb::DescriptorType::CONFIGURATION,
		.wTotalLength = sizeof(UsbConfiguration),
		.bNumInterfaces = 1,
		.bConfigurationValue = 1,
		.iConfiguration = 0,
		.bmAttributes = 0x80, // bus powered
		.bMaxPower = 50 // 100 mA
	},
	.interface = {
		.bLength = sizeof(usb::InterfaceDescriptor),
		.bDescriptorType = usb::DescriptorType::INTERFACE,
		.bInterfaceNumber = 0,
		.bAlternateSetting = 0,
		.bNumEndpoints = std::size(configurationDescriptor.endpoints),
		.bInterfaceClass = 0xff, // no class
		.bInterfaceSubClass = 0xff,
		.bInterfaceProtocol = 0xff,
		.iInterface = 0
	},
	.endpoints = {{
		.bLength = sizeof(usb::EndpointDescriptor),
		.bDescriptorType = usb::DescriptorType::ENDPOINT,
		.bEndpointAddress = 1 | usb::IN, // 1 in (device to host)
		.bmAttributes = usb::EndpointType::BULK,
		.wMaxPacketSize = 64,
		.bInterval = 1 // polling interval
	}}
};



uint8_t sendData[16];// __attribute__((aligned(4)));

// send random numbers to host
Coroutine send(UsbDevice &usb) {
	while (true) {
		// generate random numbers
		for (int i = 0; i < std::ssize(sendData); ++i)
			sendData[i] = random::u8();
		
		// send to host	
		co_await usb.send(1, sendData, std::size(sendData));

		debug::toggleBlue();		
		co_await loop::sleep(1s);
	}
}

int main() {
	loop::init();
	debug::init();
	random::init();
	board::UsbDevice usb(
		[](usb::DescriptorType descriptorType) {
			switch (descriptorType) {
			case usb::DescriptorType::DEVICE:
				return ConstData(&deviceDescriptor);
			case usb::DescriptorType::CONFIGURATION:
				return ConstData(&configurationDescriptor);
			default:
				return ConstData();
			}
		},
		[](UsbDevice &usb, uint8_t bConfigurationValue) {
			// enable bulk endpoints in 1 (keep control endpoint 0 enabled)
			usb.enableEndpoints(1 | (1 << 1), 1);

			// start to send random numbers to host
			send(usb);
		},
		[](uint8_t bRequest, uint16_t wValue, uint16_t wIndex) {
			return false;
		});

	loop::run();
}
