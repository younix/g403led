CC ?= cc
CFLAGS = -std=c99 -pedantic -Wall -Wextra

g403: g403.c
	$(CC) $(CFLAGS) -o $@ g403.c
