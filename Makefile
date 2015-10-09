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
	cp msiledenabler /usr/bin
	cp msi_kb_daemon /etc/init.d/msi_kb_daemon
	chmod 755 /etc/init.d/msi_kb_daemon
	update-rc.d msi_kb_daemon defaults
	/etc/init.d/msi_kb_daemon start

uninstall:
	#/etc/init.d/msi_kb_daemon stop
	update-rc.d -f msi_kb_daemon remove
	rm -f /usr/bin/msiledenabler
	rm -f /etc/init.d/msi_kb_daemon
	
.PHONY: clean
