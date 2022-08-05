#include "hello.h"

#include <irx.h>
#include <loadcore.h>
#include <stdio.h>

#define MODNAME "hello"
IRX_ID("IOP skeleton", 1, 1);

extern struct irx_export_table _exp_hello;

// This is a bit like a "main" for IRX files.
int _start(int argc, char *argv[])
{
    if (RegisterLibraryEntries(&_exp_hello) != 0)
        return 1;

    hello();

    return 0;
}
