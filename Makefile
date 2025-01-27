CSRC_DIR := "C"
PYTHONSRC_DIR := "python"
NANOPB_DIR = "external/nanopb-0.4.9.1-linux-x86"


CFLAGS += "-I$(NANOPB_DIR)"
CFLAGS += "-I$(CSRC_DIR)/proto"
CFLAGS += "-I$(CSRC_DIR)"


CSRC := $(wildcard C/*.c)
CSRC += $(wildcard C/proto/*.c)
NANOPB_SRC := $(NANOPB_DIR)/pb_encode.c  # The nanopb encoder
NANOPB_SRC += $(NANOPB_DIR)/pb_decode.c  # The nanopb decoder
NANOPB_SRC += $(NANOPB_DIR)/pb_common.c  # The nanopb common parts


build: $(CSRC)
	$(CC) $(CFLAGS) $(CSRC) $(NANOPB_SRC) -lraylib -o haptic_rods

proto: proto/*.proto
	$(NANOPB_DIR)/generator-bin/nanopb_generator proto/structs.proto -D$(CSRC_DIR)
	$(NANOPB_DIR)/generator-bin/protoc --python_out=$(PYTHONSRC_DIR) proto/structs.proto

run: build
	./haptic_rods

RAYLIB_PATH           ?= ../../raylib
RAYLIB_RELEASE_PATH 	?= $(RAYLIB_PATH)/src
INCLUDE_PATHS = -I. -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external -I$(RAYLIB_PATH)/src/extras
INCLUDE_PATHS += -I$(RPI_TOOLCHAIN_SYSROOT)/opt/vc/include
INCLUDE_PATHS += -I$(RPI_TOOLCHAIN_SYSROOT)/opt/vc/include/interface/vmcs_host/linux
INCLUDE_PATHS += -I$(RPI_TOOLCHAIN_SYSROOT)/opt/vc/include/interface/vcos/pthreads
INCLUDE_PATHS += -I$(RPI_TOOLCHAIN_SYSROOT)/opt/vc/include
INCLUDE_PATHS += -I$(RPI_TOOLCHAIN_SYSROOT)/opt/vc/include/interface/vmcs_host/linux
INCLUDE_PATHS += -I$(RPI_TOOLCHAIN_SYSROOT)/opt/vc/include/interface/vcos/pthreads



LDLIBS = -lraylib -lbrcmGLESv2 -lbrcmEGL -lpthread -lrt -lm -lbcm_host -ldl

LDFLAGS = -L. -L$(RAYLIB_RELEASE_PATH) -L$(RAYLIB_PATH)/src `pkg-config --libs wsserver`
LDFLAGS += -L$(RPI_TOOLCHAIN_SYSROOT)/opt/vc/lib

build_tablet: $(CSRC)
	$(CC) $(CFLAGS) $(CSRC) $(NANOPB_SRC) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -o haptic_rods