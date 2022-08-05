IOP_BIN = hello.irx
IOP_ILBS = $(PS2SDK)/iop/tab/stdio.tab $(PS2SDK)/iop/tab/loadcore.tab

IOP_OBJS = hello_main.o hello_exports.o hello_lib.o

all: $(IOP_BIN)

clean:
	rm -f -r $(IOP_OBJS) $(IOP_BIN)

include $(PS2SDK)/Defs.make
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.iopglobal
