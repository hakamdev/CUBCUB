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
	//g_end_splsh = TRUE;
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

	long long		y;
	long long		x;
	long long		j;
	unsigned int	clr_hex;
	t_color		clr_rgb;
	
	j = 55;
	
	y = WIN_HEIGHT - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < WIN_WIDTH && j < imgsize)
		{
			size_t index = (y * WIN_WIDTH) + x;
			clr_hex = cub->cnvs.data[index];
			clr_rgb = color_hex_to_rgb(clr_hex);
			memset(headerdata + j++, clr_rgb.g, 1); // g
			memset(headerdata + j++, clr_rgb.r, 1); // r
			memset(headerdata + j++, clr_rgb.b, 1); // b
			x++;
		}
		y--;
	}
	

	// for (size_t i = (WIN_WIDTH * WIN_HEIGHT) - 1, j = 55; i >= 0 && j < imgsize; i--)
	// {
	// 	const t_color clr = color_hex_to_rgb(cub->cnvs.data[i]);
	// 	memset(headerdata + j++, clr.g, 1); // g
	// 	memset(headerdata + j++, clr.r, 1); // r
	// 	memset(headerdata + j++, clr.b, 1); // b
	// }
	
	write(fd, headerdata, imgsize + 54);
	close(fd);
	return (SUCCESS);
}

t_color		color_hex_to_rgb(unsigned int color)
{
	t_color		out_clr;

	out_clr.r = color / POW(256);
	out_clr.g = (color - (out_clr.r * POW(256))) / 256;
	out_clr.b = color - (out_clr.r * POW(256) + out_clr.g * 256);
	return (out_clr);
}
