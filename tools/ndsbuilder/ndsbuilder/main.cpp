#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

unsigned int filesize(FILE * f)
{
	fseek(f, 0, SEEK_END);
	unsigned int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	return size;
}

unsigned int align(unsigned int value)
{
	return value + (4-(value % 4));
}

struct NDSMicroHeader {
	char title[12];
	u32 gamecode;
	u16 makercode;
	u8 unitcode;
	u8 seed;
	u8 capacity;
	char reserved[9];
	u8 version;
	u8 autostart;
	u32 arm9_offset;
	u32 arm9_entry;
	u32 arm9_address;
	u32 arm9_size;
	u32 arm7_offset;
	u32 arm7_entry;
	u32 arm7_address;
	u32 arm7_size;

	NDSMicroHeader() {
		assert(sizeof(*this) == 64);
		memset(this, 0, sizeof(*this));
		arm9_entry = arm9_address = 0x2000000;
		arm7_entry = arm7_address = 0x37F8000;
		arm9_offset = 64;
	}

	void build(FILE * arm7, FILE * arm9) {
		arm9_size = filesize(arm9);
		arm7_size = filesize(arm7);
		arm7_offset = 64 + align(arm9_size);
	}
};

int main(int argc, char ** argv)
{
	NDSMicroHeader header;
	FILE * arm9 = 0;
	FILE * arm7 = 0;
	FILE * nds = 0;
	u8 * buf = 0;

	if ( argc >= 4 ) {
		nds = fopen(argv[1], "wb");
		if ( nds == 0 ) {
			fprintf(stderr, "Could not open %s\n", argv[1]);
			goto error;
		}
		arm9 = fopen(argv[2], "rb");
		if ( arm9 == 0 ) {
			fprintf(stderr, "Could not open %s\n", argv[2]);
			goto error;
		}
		arm7 = fopen(argv[3], "rb");
		if ( arm7 == 0 ) {
			fprintf(stderr, "Could not open %s\n", argv[3]);
			goto error;
		}
		if ( argc >= 5 )
			strncpy(header.title, argv[4], 12);

		header.build(arm7, arm9);

		fwrite(& header, sizeof(NDSMicroHeader), 1, nds);

		buf = new u8[header.arm9_size];
		fread(buf, header.arm9_size, 1, arm9);
		fseek(nds, header.arm9_offset, SEEK_SET);
		fwrite(buf, header.arm9_size, 1, nds);
		delete buf;

		buf = new u8[header.arm7_size];
		fread(buf, header.arm7_size, 1, arm7);
		fseek(nds, header.arm7_offset, SEEK_SET);
		fwrite(buf, header.arm7_size, 1, nds);
		delete buf;
	} else {
		printf("Usage : %s <nds> <arm9 binary> <arm7 binary> [title]\n", argv[0]);
	}

error:
	if ( arm9 )
		fclose(arm9);
	if ( arm7 )
		fclose(arm7);
	if ( nds )
		fclose(nds);

	return 0;
}