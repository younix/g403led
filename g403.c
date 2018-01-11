#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <libusb.h>

int
main(void)
{
	int ret = 0;
	libusb_context *ctx = NULL;
	libusb_device **devs;
	libusb_device *dev = NULL;
	libusb_device_handle *handle = NULL;

	if (libusb_init(&ctx) < 0)
		errx(EXIT_FAILURE, "libusb_init");

	ssize_t cnt = libusb_get_device_list(ctx, &devs);
	for (ssize_t i = 0; i < cnt; i++) {
		libusb_device *device = devs[i];
		struct libusb_device_descriptor desc;
		libusb_get_device_descriptor(device, &desc);

//printf("id: 0x%04x : 0x%04x\n", desc.idVendor, desc.idProduct);

		if (desc.idVendor == 0x046d && desc.idProduct == 0xC083) {
			printf("found\n");
			dev = device;
		}
	}

	if (dev == NULL)
		errx(EXIT_FAILURE, "device not found");

	if ((ret = libusb_open(dev, &handle)) != 0)
		errx(EXIT_FAILURE, "libusb_open");

// * 11:ff:0e:3b : 01 : 01 : 02:02:02 : 02 : 00:00:00:00:00:00:00:00:00:00

//	data.push_back(static_cast<uint8_t>( static_cast<uint16_t>(SortedKeys[kag][gi+i].key) & 0x00ff) - 1);
//	data.push_back(0x01);
//	data.push_back(SortedKeys[kag][gi+i].color.red);
//	data.push_back(SortedKeys[kag][gi+i].color.green);
//	data.push_back(SortedKeys[kag][gi+i].color.blue);
//	data.push_back(0x02);

	uint8_t red   = 0xff;
	uint8_t green = 0x0f;
	uint8_t blue  = 0x0f;

	uint8_t data[10] = {
		0x11,
		0xff,
		0x0e,
		0x3b,
		0x00, // wheel or logo (1 / 0)

		0x01,
		red,
		green,
		blue,
		0x02
	};

	libusb_claim_interface(handle, 2);

	ret = libusb_control_transfer(handle, 0x21, 0x09, 0x0211, 1, data, sizeof data, 2000);
	if (ret < 0)
		errx(EXIT_FAILURE, "libusb_control_transfer: %s", libusb_error_name(ret));

	usleep(1000);

	/* data > 20 -> 0x82 */
	/* data < 20 -> 0x83 */
	int len = 0;
	unsigned char buffer[64];
	ret = libusb_interrupt_transfer(handle, 0x83, buffer, sizeof buffer, &len, 2000);

	printf("len: %d\n", len);

	return EXIT_SUCCESS;
}
