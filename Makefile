CC ?= cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra
LIBUSB = `pkg-config --cflags --libs libusb`

g403: g403.c
	$(CC) $(CFLAGS) $(LIBUSB) -o $@ g403.c
