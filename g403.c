#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <hid.h>

int
main(void)
{
	int ret = 0;
//	struct hid_device_info *devs, *dev;
	HIDInterface handle;
	memset(&handle, 0, sizeof handle);

	if (hid_init() != HID_RET_SUCCESS)
		errx(EXIT_FAILURE, "hid_init");

//	devs = hid_enumerate(0x0, 0x0);
//	for (dev = devs; dev != NULL; dev = dev->next) {
//		printf("0x%04x 0x%04x %s\n", dev->vendor_id, dev->product_id,
//		    dev->product_string);

//		if (dev->vendor_id == 0x046d && dev->product_id == 0xC083) {
//			printf("found\n");
//			handle = hid_open(currentDevice.vendorID,
//			    currentDevice.productID, NULL);
//		}
//	}

//	hid_free_enumeration(devs);

	HIDInterfaceMatcher matcher;
	memset(&matcher, 0, sizeof matcher);
	matcher.vendor_id  = 0x046d;
	matcher.product_id = 0xC083;

	ret = hid_open(&handle, 0, &matcher);

	if (ret != HID_RET_SUCCESS)
		errx(EXIT_FAILURE, "hid_open");

	if (hid_is_opened(&handle) == false)
		errx(EXIT_FAILURE, "device not found");

// * 11:ff:0e:3b : 01 : 01 : 02:02:02 : 02 : 00:00:00:00:00:00:00:00:00:00

//	data.push_back(static_cast<uint8_t>( static_cast<uint16_t>(SortedKeys[kag][gi+i].key) & 0x00ff) - 1);
//	data.push_back(0x01);
//	data.push_back(SortedKeys[kag][gi+i].color.red);
//	data.push_back(SortedKeys[kag][gi+i].color.green);
//	data.push_back(SortedKeys[kag][gi+i].color.blue);
//	data.push_back(0x02);

	char red   = 0xff;
	char green = 0x0f;
	char blue  = 0x0f;

	char data[10] = {
//		0x00,// for hid
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

	ret = hid_interrupt_write(&handle, 0, data, sizeof data, 2000);
	if (ret < 0)
		errx(EXIT_FAILURE, "hid_write");

	hid_close(&handle);
	hid_cleanup();

	return EXIT_SUCCESS;
}
