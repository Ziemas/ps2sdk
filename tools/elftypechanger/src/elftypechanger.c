/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2022, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

unsigned char *buffer;

int main(int argc, char *argv[])
{
	int fd_size;
	FILE *source, *dest;
	char *e_type_chr_end;
	uint16_t e_type_int;

	if (argc != 4)
	{
		printf("elftypechanger\n"
			   "Usage: elftypechanger infile outfile e_type\n\n");
		return 1;
	}

	if (argv[3][0] == '\x00')
	{
		printf("Argument 3 is empty.\n");
		return 1;
	}

	e_type_chr_end = NULL;
	e_type_int = (uint16_t)strtoul(argv[3], &e_type_chr_end, 16);
	if (e_type_chr_end == NULL || *e_type_chr_end != '\x00')
	{
		printf("Argument 3 does is not a hexadecimal number.\n");
		return 1;
	}

	if ((source = fopen(argv[1], "rb")) == NULL)
	{
		printf("Error opening %s for reading.\n",argv[1]);
		return 1;
	}

	fseek(source, 0, SEEK_END);
	fd_size = ftell(source);
	fseek(source, 0, SEEK_SET);

	buffer = malloc(fd_size);
	if (buffer == NULL)
	{
		printf("Failed to allocate memory.\n");
		fclose(source);
		return 1;
	}

	if (fread(buffer, 1, fd_size, source) != fd_size)
	{
		printf("Failed to read file.\n");
		fclose(source);
		return 1;
	}
	fclose(source);

	if (fd_size < 18)
	{
		printf("File is too small to be an ELF.\n");
		return 1;
	}

	if (memcmp("\177ELF", buffer, 4) != 0)
	{
		printf("File does not appear to be ELF.\n");
		return 1;
	}

	*((uint16_t *)(buffer + 16)) = e_type_int;

	if ((dest = fopen(argv[2], "w")) == NULL)
	{
		printf("Failed to open/create %s.\n", argv[2]);
		return 1;
	}

	if (fwrite(buffer, 1, fd_size, dest) != fd_size)
	{
		printf("Failed to write modified file.\n");
		fclose(dest);
		return 1;
	}

	fclose(dest);

	return 0;
}
