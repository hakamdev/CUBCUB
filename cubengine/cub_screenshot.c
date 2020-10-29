#include "../include/cubengine.h"
#include "../include/get_next_line.h"

int		take_screenshot(t_cub *cub)
{
	t_bmp	bmp;
	unsigned char *headerdata;
	unsigned char *buff;
	unsigned char *bufftemp;
	int fd;

	fd = open("ss.bmp", O_RDWR);
	g_end_splsh = TRUE;
	event_game_loop(cub);
	bmp.info.bpp = 24;
	uint32_t wipixel = ((WIN_WIDTH * bmp.info.bpp + 31) / 32) *4;
	uint32_t imgsize = wipixel * WIN_HEIGHT;
	headerdata = (unsigned char *)malloc((imgsize + 54) * sizeof(unsigned char));
	bmp.info.headersize = 40;
	bmp.header.offset = 54;
	bmp.header.filesize = 54 + imgsize;
	bmp.info.planes = 1;

	memcpy(headerdata, "BM", 2);
	memcpy(headerdata + 2, &bmp.header.filesize, 4);
	memcpy(headerdata + 10, &bmp.header.offset, 4);
	memcpy(headerdata + 14, &bmp.info.headersize, 4);
	memcpy(headerdata + 18, &WIN_WIDTH, 4);
	memcpy(headerdata + 22, &WIN_HEIGHT, 4);
	memcpy(headerdata + 26, &bmp.info.planes, 2);
	memcpy(headerdata + 28, &bmp.info.bpp, 2);

	for (size_t i = (WIN_WIDTH * WIN_HEIGHT) - 1, j = 55; i >= 0 && j < imgsize; i--)
	{
		unsigned char r, g, b;
		int clr = cub->cnvs.data[i];
		r = clr / POW(256);
		g = (clr - (r * POW(256))) / 256;
		b = clr - (r * POW(256) + g * 256);
		memset(headerdata + j++, g, 1); // g
		memset(headerdata + j++, r, 1); // r
		memset(headerdata + j++, b, 1); // b
	}
	
	write(fd, headerdata, imgsize + 54);
	close(fd);
	return (SUCCESS);
}

