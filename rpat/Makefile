#!/usr/bin/make -f

CC = gcc
CFLAGS = -g -static
BFD_ROOT = $(HOME)/binutils-2.22
LIB_ROOT = $(BFD_ROOT)/bfd/
INCS = -I $(BFD_ROOT) -I $(BFD_ROOT)/bfd -I $(BFD_ROOT)/include -I $(BFD_ROOT)/binutils -I $(BFD_ROOT)/intl
LD_FLAGS = -L $(LIB_ROOT) -L $(BFD_ROOT)/libiberty 
# -L $(BFD_ROOT)/intl
LIBS = -lbfd -liberty -lintl -liconv
OBJS = $(BFD_ROOT)/binutils/bucomm.o $(BFD_ROOT)/binutils/filemode.o

all: rpat

rpat: rpat.o crc16.o llist.o
	$(CC) $(LD_FLAGS) -static rpat.o crc16.o llist.o $(OBJS) -o $@ $(LIBS)
#	strip $@

rpat.o: rpat.c
	$(CC) $(INCS) -c rpat.c
	    
crc16.o: crc16.c

llist.o: llist.c

test: rpat
	./rpat /usr/lib/libc_r.a | less
	
clean:
	-rm -f *.o rpat.exe