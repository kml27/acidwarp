/* Bit_Map Image Uncompressor (C)Copyright 1992 by Noah Spurrier	*/

#include <stdlib.h>
#include "handy.h"
#include "bit_map.h"

/* Bit Map is 2 Bits per pixel, with 4 pixels per byte. The 4 pixels are
 * in a horizontal row. I.e. 1234 NOT 1 NOR 4
 *                                    2     3
 *                                    3     2
 *                                    4     1
 */

static UCHAR TITLE_DATA [(X_TITLE * Y_TITLE / 4)] =
{ 
	 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85,
	 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85,
	 85, 85, 85, 85, 85, 85,117, 85, 85, 85,117, 85, 85, 85,117, 85, 85,213, 85, 85,
	 85, 85, 85, 85, 85, 87,213, 85, 85, 87,213, 85, 85, 87,213, 85, 95, 85, 85, 85,
	 85, 85, 85, 85, 85,127,213, 85, 85,127, 85, 85, 85,127, 85, 85,255, 85, 85, 85,
	 85, 85, 85, 85, 85,255,213, 85, 85,253, 85, 85, 85,253, 85, 87,255, 85, 85, 85,
	 85, 85, 85, 85, 87,247,213, 85, 87,245, 85, 85, 87,245, 85, 95,223, 85, 85, 85,
	 85, 85, 85, 85,127,215,213, 85,127,213, 85, 85,127,213, 85,255, 95, 85, 85, 85,
	 85, 85, 85, 85,255, 87,213, 85,255, 85, 85, 85,255, 85, 87,253, 95, 85, 85, 85,
	 85, 85, 85, 87,253, 87,213, 87,253, 85, 85, 87,253, 85, 95,245, 95, 85, 85, 85,
	 85, 85, 85, 95,245, 87,213, 95,245, 85, 85, 95,245, 85,127,213, 95, 85, 85, 85,
	 85, 85, 85,127,245, 87,213,127,245, 85, 85,127,245, 85,255,213, 95, 85, 85, 85,
	 85, 85, 85,255,255,255,213,255,213, 85, 85,255,213, 87,255, 85, 95, 85, 85, 85,
	 85, 85, 85,255,255,255,213,255,213, 85, 85,255,213, 87,255, 85, 95, 85, 85, 85,
	 85, 85, 87,255,213, 87,215,255,213, 85, 87,255,213, 95,255, 85, 95, 85, 85, 85,
	 85, 85, 87,255,213, 87,215,255,213, 85, 87,255,213, 95,255, 85, 95, 85, 85, 85,
	 85, 85, 87,255,213, 87,215,255,213, 85, 87,255,213, 95,255, 85, 95, 85, 85, 85,
	 85, 85, 87,255,213, 87,215,255,255,255,215,255,213, 95,255,255,255, 85, 85, 85,
	 85, 85, 87,255,213, 87,215,255,255,255,215,255,213, 95,255,255,255, 85, 85, 85,
	 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85,
	 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85,
	170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
	170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
	170,170,170,170,170,170,170,170,170,128,  0,  0,  0,170,170,170,170,170,170,170,
	170,170,170,170,170,170,170,168,  0,  0,  0,  0,  0,  0,  2,170,170,170,170,170,
	170,170,170,170,170,170,168,  0,  0,  0,  0,  0,  0,  0,  0,  0,170,170,170,170,
	170,170,170,170,170,170,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 10,170,170,170,
	170,170,170,170,170,160,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 42,170,170,170,
	170,170,170,170,168,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,170,170,170,170,
	170,170,170,170,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,170,170,170,170,
	170,170,170,170,  0,  0,  0,  0,  0,170,168,  0,  0,  0,  0,  0,170,170,170,170,
	170,170,170,160,  0,  0,  0, 10,170,171,255,252,  0,255,255,  0, 42,170,170,170,
	170,170,170,128,  0,  0, 22,170,171,255,255,255,255,255,255,233, 10,170,170,170,
	170,170,170,  0,  0,  1,106,170,255,255,255,255,255,255,255,255,146,170,170,170,
	170,170,168,  0,  0, 22,170,175,255,255,255,255,255,255,255,255,228,170,170,170,
	170,170,160,  0,  0, 90,170,191,255,255,255,255,255,255,255,255,254,170,170,170,
	170,170,160,  0,  1,106,170,255,255,255,255,255,255,255,255,255,255,170,170,170,
	170,170,160,  0,  5,106,170,255,255,255,255,255,255,255,255,255,255,234,170,170,
	170,170,160,  0,  5,106,170,255,255,255,255,255,255,255,255,255,255,234,170,170,
	170,170,160,  0,  5, 90,170,255,255,255,255,255,255,255,255,255,255,234,170,170,
	170,170,160,  0,  5, 86,170,191,255,255,255,255,255,255,255,255,255,234,170,170,
	170,170,160,  0,  5, 85,170,  0,  0,  3,255,255,255,255,255,255,255,234,170,170,
	170,170,160,  0,  1, 85,  0,  0,  0,  0, 63,255,255,192,  0,  0, 47,234,170,170,
	170,170,160,  0,  0, 80,  2,170,169, 85,107,255,255,  0, 85, 85,  2,170,170,170,
	170,170,160,  0,  0,  0, 22,169, 85, 85, 90,255,253, 86,191,255,226,170,170,170,
	170,170,160,  0,  1, 80, 85, 85, 21, 85, 90,191,253, 85, 69,255,232,170,170,170,
	170,170,134,144,  5, 85, 85, 80,  2,149,106,191,254,149,  0, 90,170,170,170,170,
	170,170,  6, 96, 21, 90,149,104, 10,191,170,191,255,175, 66,165,170,250,170,170,
	170,170,  6,  0, 21,106,170,170,170,255,170,191,255,234,170,170,255,234,170,170,
	170,170,  8, 36, 21,106,191,255,255,255,170,255,255,255,255,255,254,170,170,170,
	170,170,138,170,  5, 90,255,255,255,255,170,255,255,255,255,255,254,170,170,170,
	170,170,138,  2,  0, 90,191,255,255,255,171,255,255,255,255,255,254,170,170,170,
	170,170,133, 40,  0, 22,175,255,255,250,171,255,255,255,255,255,255,170,170,170,
	170,170,160,170,  0, 22,175,255,255,245, 86,175,235,255,255,255,251,170,170,170,
	170,170,168,170,  0, 85,171,255,255,233,106, 86,150,255,255,255,239,170,170,170,
	170,170,170,  1, 65, 85,170,255,255,234,170,175,255,255,255,255,239,170,170,170,
	170,170,170,170,129, 85,106,191,255,234,175,255,255,255,255,255,174,170,170,170,
	170,170,170,170,161, 85,106,171,255,170,255,255,255,255,255,255,170,170,170,170,
	170,170,170,170,160, 85, 90,170,170,165, 85, 85,175,255,255,254,170,170,170,170,
	170,170,170,170,168, 21, 86,170,168,  0,  0,  0,  0, 43,255,250,170,170,170,170,
	170,170,170,170,170,  5, 85,170,170,170,191,255,254,255,255,234,170,170,170,170,
	170,170,170,170,170,160, 85, 90,170,170, 85, 86,170,255,254,170,170,170,170,170,
	170,170,170,170,170,170,  5, 85,170,170,170,170,175,255,250,170,170,170,170,170,
	170,170,170,170,170,170,160, 85,106,175,255,255,255,255,168,170,170,170,170,170,
	170,170,170,170,170,170,170,  5, 90,191,255,255,255,250,138,170,170,170,170,170,
	170,170,170,170,170,170,170,160, 85,175,255,255,255,232,170,170,170,170,170,170,
	170,170,170,170,170,170,170,170,  1,106,191,255,252, 10,170,170,170,170,170,170,
	170,170,170,170,170,170,170,170,168,  0,  0,  0,  2,170,170,170,170,170,170,170,
	170,170,170,170,170,170,170,170,170,160,  0,  0,170,170,170,170,170,170,170,170,
	170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
	170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,
	 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85,
	 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85,
	 85, 85, 85, 85,213, 85, 85, 85,117, 85, 85,213, 85, 85, 85,213, 85, 85, 85,213,
	 85, 85, 85, 95, 85, 85, 85, 87,213, 85, 95, 85, 85, 85, 95, 85, 85, 85, 95, 85,
	 85, 85, 85,253, 85, 85, 85,127, 85, 85,255, 85, 85, 85,255, 85, 85, 85,255, 85,
	 85, 85, 87,245, 85, 85, 85,253, 85, 87,255, 85, 85, 87,255, 85, 85, 87,255, 85,
	 85, 85, 95,213, 85, 85, 87,245, 85, 95,223, 85, 85, 95,223, 85, 85, 95,223, 85,
	 85, 85,255, 85, 85, 85,127,213, 85,255, 95, 85, 85,255, 95, 85, 85,255, 95, 85,
	 85, 87,253, 85, 85, 85,255, 85, 87,253, 95, 85, 87,253, 95, 85, 87,253, 95, 85,
	 85, 95,245, 85, 85, 87,253, 85, 95,245, 95, 85, 95,245, 95, 85, 95,245, 95, 85,
	 85,127,213, 85, 85, 95,245, 85,127,213, 95, 85,127,213, 95, 85,127,213, 95, 85,
	 85,255,213, 85, 85,127,245, 85,255,213, 95, 85,255,213, 95, 85,255,213, 95, 85,
	 87,255, 85, 85,213,255,213, 87,255,255,255, 87,255,255,255, 87,255,255,255, 85,
	 87,255, 85,127, 85,255,213, 87,255,255,255, 87,255,255,255, 87,255,255,255, 85,
	 95,255, 87,255,215,255,213, 95,255, 85, 95, 95,255,253, 85, 95,255, 85, 85, 85,
	 95,255,127,215,247,255,213, 95,255, 85, 95, 95,255, 95,213, 95,255, 85, 85, 85,
	 95,255,253, 85,127,255,213, 95,255, 85, 95, 95,255, 85,253, 95,255, 85, 85, 85,
	 95,255,245, 85, 95,255,213, 95,255, 85, 95, 95,255, 85,127, 95,255, 85, 85, 85,
	 95,255, 85, 85, 87,255,213, 95,255, 85, 95, 95,255, 85,127, 95,255, 85, 85, 85,
	 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85,
	 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85,
	 87,247,255,127, 93, 85, 95,215,245,215, 85,127,245,245, 85,255,117,119,127,245,
	 93, 85,117,117,221, 85, 93,119, 93,221, 85, 87, 87, 93, 85,213, 93,215, 87, 85,
	 93, 85,117,127, 93, 95,223,215,245,245, 85, 87, 87, 93, 85,253, 87, 87, 87, 85,
	 93, 85,117,119, 93, 85, 93,119, 93,221, 85, 87, 87, 93, 85,213, 93,215, 87, 85,
	 87,245,117,117,223,213, 95,215, 93,215, 85, 87, 85,245, 85,255,117,119, 87, 85,
	 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85, 85,
};


/* This function assumes that the colors 0, 9, 17, and 25 will be
 * appropriate for the current palette. See 'switch (bits)' below.
 */

static void bit_map_uncompress (UCHAR *buf_graf, UCHAR *bit_data,
                                int x_map, int y_map, int xmax, int ymax)
{
	int x, y, tx, ty;

	int beg_x, beg_y, end_x, end_y;

	int bits2;

	int xsize;
	
	xsize = xmax + 1;

	beg_x = (xmax - 2 * x_map) / 2;
	beg_y = (ymax - 2 * y_map) / 2;
	end_x = 2 * x_map + beg_x;
	end_y = 2 * y_map + beg_y;

	if (beg_x < 0 || beg_y < 0 || end_x >= xmax || end_y >= ymax)
		return;

	for (y = beg_y; y < end_y; y += 2)
	{
		for (x = beg_x; x < end_x; x += 2)
		{
			tx = (x - beg_x) / 2;
			ty = (y - beg_y) / 2;

			bits2 = *(bit_data + ((x_map * ty + tx) / 4) );

			switch ((x_map * ty + tx) % 4)
			{
				case 0:
					bits2  &= 0xc0;
					bits2 >>= 6;
				break;

				case 1:
					bits2  &= 0x30;
					bits2 >>= 4;
				break;

				case 2:
					bits2  &= 0x0c;
					bits2 >>= 2;
				break;

				case 3:
					bits2  &= 0x03;
				break;
			}

			switch (bits2)
			{
/*       	case 0 :
          writePixel(x,   y,   RANDOM(8) + 192 + 0);
          writePixel(x+1, y,   RANDOM(8) + 192 + 0);
          writePixel(x,   y+1, RANDOM(8) + 192 + 0);
          writePixel(x+1, y+1, RANDOM(8) + 192 + 0);
				break;

				case 1 :
          writePixel(x,   y,   RANDOM(8) + 192 + 9);
          writePixel(x+1, y,   RANDOM(8) + 192 + 9);
          writePixel(x,   y+1, RANDOM(8) + 192 + 9);
          writePixel(x+1, y+1, RANDOM(8) + 192 + 9);
				break;

				case 2 :
          writePixel(x,   y,   RANDOM(8) + 192 + 17);
          writePixel(x+1, y,   RANDOM(8) + 192 + 17);
          writePixel(x,   y+1, RANDOM(8) + 192 + 17);
          writePixel(x+1, y+1, RANDOM(8) + 192 + 17);
				break;

				case 3 :
          writePixel(x,   y,   RANDOM(8) + 192 + 25);
          writePixel(x+1, y,   RANDOM(8) + 192 + 25);
          writePixel(x,   y+1, RANDOM(8) + 192 + 25);
          writePixel(x+1, y+1, RANDOM(8) + 192 + 25);
				break;
			}
*/
				case 0 :
          *(buf_graf + xsize * (y+0) + (x+0)) = (UCHAR)RANDOM(8) + 192 + 0;
          *(buf_graf + xsize * (y+1) + (x+0)) = (UCHAR)RANDOM(8) + 192 + 0;
          *(buf_graf + xsize * (y+0) + (x+1)) = (UCHAR)RANDOM(8) + 192 + 0;
          *(buf_graf + xsize * (y+1) + (x+1)) = (UCHAR)RANDOM(8) + 192 + 0;
				break;

				case 1 :
          *(buf_graf + xsize * (y+0) + (x+0)) = (UCHAR)RANDOM(8) + 192 + 9;
          *(buf_graf + xsize * (y+1) + (x+0)) = (UCHAR)RANDOM(8) + 192 + 9;
          *(buf_graf + xsize * (y+0) + (x+1)) = (UCHAR)RANDOM(8) + 192 + 9;
          *(buf_graf + xsize * (y+1) + (x+1)) = (UCHAR)RANDOM(8) + 192 + 9;
				break;

				case 2 :
          *(buf_graf + xsize * (y+0) + (x+0)) = (UCHAR)RANDOM(8) + 192 + 17;
          *(buf_graf + xsize * (y+1) + (x+0)) = (UCHAR)RANDOM(8) + 192 + 17;
          *(buf_graf + xsize * (y+0) + (x+1)) = (UCHAR)RANDOM(8) + 192 + 17;
          *(buf_graf + xsize * (y+1) + (x+1)) = (UCHAR)RANDOM(8) + 192 + 17;
				break;

				case 3 :
          *(buf_graf + xsize * (y+0) + (x+0)) = (UCHAR)RANDOM(8) + 192 + 25;
          *(buf_graf + xsize * (y+1) + (x+0)) = (UCHAR)RANDOM(8) + 192 + 25;
          *(buf_graf + xsize * (y+0) + (x+1)) = (UCHAR)RANDOM(8) + 192 + 25;
          *(buf_graf + xsize * (y+1) + (x+1)) = (UCHAR)RANDOM(8) + 192 + 25;
				break;
			}
		}
	}
}

void writeBitmapImageToArray (UCHAR *buf_graf, int image_number, int xmax, int ymax)
{
	switch (image_number)
	{
		case NOAHS_FACE:	/* TITLE IMAGE */
			bit_map_uncompress (buf_graf, TITLE_DATA, X_TITLE, Y_TITLE, xmax, ymax);
		break;

		default:
		break;
	}
}

