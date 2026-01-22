###########################################
# Simple Makefile for HIDAPI test program
#
# Alan Ott
# Signal 11 Software
# 2010-07-03
###########################################

all: msiledenabler

CC=gcc
CXX=g++
#COBJS=hid.o 
CPPOBJS=msg.o msiledenabler.o 
OBJS=$(COBJS) $(CPPOBJS)
CFLAGS+=-Ihidapi -Wall -g -c 
LIBS=-ludev -lhidapi-libusb


msiledenabler: $(OBJS)
	g++ -Wall -g $^ $(LIBS) -o msiledenabler

$(COBJS): %.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(CPPOBJS): %.o: %.cpp
	$(CXX) $(CFLAGS) $< -o $@

clean:
	rm -f *.o msiledenabler $(CPPOBJS)

install:
	-systemctl stop msi-led-enabler.service
	cp msiledenabler /usr/bin
	cp msi-led-enabler.service /etc/systemd/system/
	systemctl daemon-reload
	systemctl enable msi-led-enabler.service
	systemctl start msi-led-enabler.service
	cp 99-msi-led.rules /etc/udev/rules.d/
	udevadm control --reload-rules && udevadm trigger

uninstall:
	systemctl stop msi-led-enabler.service
	systemctl disable msi-led-enabler.service
	rm -f /etc/systemd/system/msi-led-enabler.service
	rm -f /etc/udev/rules.d/99-msi-led.rules
	udevadm control --reload-rules && udevadm trigger
	rm -f /usr/bin/msiledenabler
	
.PHONY: clean
