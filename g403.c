#include <sys/ioctl.h>

#include <dev/usb/usb.h>
#include <dev/usb/usbhid.h>

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main(void)
{
	int fd;
//	matcher.vendor_id  = 0x046d;
//	matcher.product_id = 0xC083;

	if ((fd = open("/dev/uhid3", O_RDWR)) == -1)
		err(EXIT_FAILURE, "open");

	char red   = 0xff;
	char green = 0x0f;
	char blue  = 0x0f;

	char = 0x0f;

	char data[9] = {
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

	struct usb_ctl_report report;
	report.ucr_report = 0x2;
	memcpy(report.ucr_data, data, sizeof data);

	if (ioctl(fd, USB_SET_REPORT, &report) == -1)
		err(EXIT_FAILURE, "ioctl");

	if (close(fd) == -1)
		err(EXIT_FAILURE, "close");

	return EXIT_SUCCESS;
}
