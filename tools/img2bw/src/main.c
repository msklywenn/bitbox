// $ gcc -o img21bppraw img21bppraw.c -lfreeimage

#include <stdio.h>
#include <FreeImage.h>

FIBITMAP * loadimage(const char * input)
{
    FREE_IMAGE_FORMAT fif;
	FIBITMAP * image = 0;

	fif = FreeImage_GetFileType((const char *) input, 0);
	if ( fif == FIF_UNKNOWN ) {
		return 0;
	}

	image = FreeImage_Load(fif, (const char *) input, BMP_DEFAULT);
	FreeImage_FlipVertical(image);

	return image;
}

int main(int argc, char ** argv)
{
	int bpp;
	FILE * f;
	if ( argc != 3 )
		return -1;

	FIBITMAP * img = loadimage(argv[1]);
	if ( img == 0 )
		return -2;

	f = fopen(argv[2], "wb");
	if ( f== 0 )
		return -3;

	bpp = FreeImage_GetBPP(img);
	unsigned char * bits = FreeImage_GetBits(img);
	int i, w, h;

	w = FreeImage_GetWidth(img);
	h = FreeImage_GetHeight(img);

	unsigned char buffer = 0, b = 0;

	for ( i = w * h ; i > 0 ; i--, bits += (bpp / 8)) {
		if ( *bits > 0 )
			buffer |= (1<<b);
		b++;

		if ( b == 8 ) {
			fwrite(& buffer, 1, 1, f);
			b = 0;
			buffer = 0;
		}
	}

	FreeImage_Unload(img);
	fclose(f);

	return 0;
}
