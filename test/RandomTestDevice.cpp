#include <coco/debug.hpp>
#include <RandomTestDevice.hpp>


/*
	Random test USB device
*/

using namespace coco;

// device descriptor
static const usb::DeviceDescriptor deviceDescriptor = {
	//.bLength = sizeof(usb::DeviceDescriptor),
	//.bDescriptorType = usb::DescriptorType::DEVICE,
	//.bcdUSB = 0x0200, // USB 2.0
	.bDeviceClass = usb::DeviceClass::VENDOR,
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
	struct usb::ConfigurationDescriptor config;
	struct usb::InterfaceDescriptor interface;
	struct usb::EndpointDescriptor endpoints[2];
};

static const UsbConfiguration configurationDescriptor = {
	.config = {
		//.bLength = sizeof(usb::ConfigurationDescriptor),
		//.bDescriptorType = usb::DescriptorType::CONFIGURATION,
		.wTotalLength = sizeof(UsbConfiguration),
		.bNumInterfaces = 1,
		.bConfigurationValue = 1,
		.iConfiguration = 0,
		.bmAttributes = 0x80, // bus powered
		.bMaxPower = 50 // 100 mA
	},
	.interface = {
		//.bLength = sizeof(usb::InterfaceDescriptor),
		//.bDescriptorType = usb::DescriptorType::INTERFACE,
		.bInterfaceNumber = 0,
		.bAlternateSetting = 0,
		.bNumEndpoints = std::size(configurationDescriptor.endpoints),
		.bInterfaceClass = usb::InterfaceClass::VENDOR,
		.bInterfaceSubClass = 0xff,
		.bInterfaceProtocol = 0xff,
		.iInterface = 0
	},
	.endpoints = {
		{
			//.bLength = sizeof(usb::EndpointDescriptor),
			//.bDescriptorType = usb::DescriptorType::ENDPOINT,
			.bEndpointAddress = 1 | usb::IN, // 1 in (device to host)
			.bmAttributes = usb::EndpointType::BULK,
			.wMaxPacketSize = 64,
			.bInterval = 1 // polling interval
		},
		{
			//.bLength = sizeof(usb::EndpointDescriptor),
			//.bDescriptorType = usb::DescriptorType::ENDPOINT,
			.bEndpointAddress = 2 | usb::IN, // 2 in (device to host)
			.bmAttributes = usb::EndpointType::BULK,
			.wMaxPacketSize = 64,
			.bInterval = 1 // polling interval
		}
	}
};


// handle control requests
Coroutine control(UsbDevice &device, Buffer &buffer) {
	while (true) {
		// wait for a control request (https://www.beyondlogic.org/usbnutshell/usb6.shtml)
		co_await device.untilRequest();
		auto setup = device.getSetup();

		// handle request
		switch (setup.bmRequestType) {
		case usb::RequestType::STANDARD_DEVICE_IN:
			switch (setup.bRequest) {
			case usb::Request::GET_DESCRIPTOR:
				{
					auto descriptorType = usb::DescriptorType(setup.wValue >> 8);
					//int descriptorIndex = setup.value & 0xff;
					switch (descriptorType) {
					case usb::DescriptorType::DEVICE:
						co_await UsbDevice::controlIn(buffer, setup, deviceDescriptor);
						break;
					case usb::DescriptorType::CONFIGURATION:
						co_await UsbDevice::controlIn(buffer, setup, configurationDescriptor);
						break;
					//case usb::DescriptorType::STRING:
					default:
						device.stall();
					}
				}
				break;
			default:
				device.stall();
			}
			break;
		default:
			device.stall();
		}
	}
}

// send random numbers to host
Coroutine generate(Loop &loop, Random &random, Buffer &usb) {
	while (true) {
		// wait until buffer is ready (device is connected)
		co_await usb.untilReady();

		while (usb.ready()) {
			// generate random number
			random.draw(usb.data(), 4);
			debug::toggleBlue();

			// send to host
			co_await usb.write(4);

			debug::toggleGreen();

			co_await loop.sleep(100ms);
		}
	}
}

int main() {
	// handle control requests
	control(drivers.device, drivers.controlBuffer);

	// start to send random numbers to host
	generate(drivers.loop, drivers.random, drivers.usb1);

	drivers.loop.run();
}
