#
# Makefile for up
#

CC		= gcc
#CC	= cc

CFLAGS	= -O2 -Wall

up:
	$(CC) $(CFLAGS) -o up up.c

clean:
	rm -f up.o core up

all:
	up
