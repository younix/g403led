CC ?= cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra
PREFIX ?= /usr/local

.PHONY: all clean install

all: g403
g403: g403.c
	$(CC) $(CFLAGS) -o $@ g403.c

clean:
	rm -f g403

install: all
	install -m 775 g403 ${PREFIX}/bin
	install -m 444 g403.1 ${PREFIX}/man/man1
