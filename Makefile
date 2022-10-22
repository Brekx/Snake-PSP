SHELL := /bin/sh

TARGET = sprite
OBJS = src/graphic.o src/main.o src/callbacks.o src/vram.o texture.o

INCDIR = "/usr/include/c++/11.2.1/" "inc"
CFLAGS = -Wall -O3
CXXFLAGS = $(CFLAGS) -fno-rtti -fexceptions -std=c++17
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS= -lpspgum -lpspgu -lstdc++

EXTRA_TARGETS = EBOOT.PBP
NOW=$(shell date '+%F_%H:%M:%S' )
PSP_EBOOT_TITLE = Snake ${NOW}

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

texture.o: res/texture.raw
	bin2o -i res/texture.raw texture.o texture
with_psp_flash:
	@./scripts/print.sh 11 "Compiling\n"
	make all
	@./scripts/print.sh 11 "Waiting for device ...\n"
	@./scripts/docker_machine.sh
	@./scripts/print.sh 2 "Done!\n"
	@./scripts/print.sh 11 "Cleaning ...\n"
	make clean
	@./scripts/print.sh 11 "File "