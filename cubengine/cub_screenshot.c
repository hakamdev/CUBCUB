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

	// write(fd, headerdata, 54);
	// buff = (unsigned char *)malloc(imgsize * sizeof(unsigned char));
	// bufftemp = buff;

	for (size_t i = (WIN_WIDTH * WIN_HEIGHT) - 1, j = 55; i >= 0 && j < imgsize; i--)
	{
		unsigned char r, g, b;
		int clr = cub->cnvs.data[i];
		r = (float)clr / POW(255);
		g = ((float)clr - r) / 255;
		b = clr - (r + g);
		//printf("\nr: %d g: %d b: %d\n", r, g, b);
		memset(headerdata + j++, r, 1);
		memset(headerdata + j++, g, 1);
		memset(headerdata + j++, b, 1);
	}
	
	write(fd, headerdata, imgsize + 54);
	// memset(buff, 0x0000FF, imgsize - 10000);
	// char *c = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
	// write(fd, buff, imgsize - 10000);
	close(fd);
	return (SUCCESS);
}


// int		take_screenshot(t_cub *cub)
// {
// 	int fd;
// 	t_bmp *bmp;

	
// 	// if (!(fd = open("ss.bmp", O_CREAT | O_RDWR | O_APPEND)))
// 	// 	return (ft_output(cub->errno, exit_error(cub, "Nood 3la slaamtek!")));
	
// 	FILE *fp = fopen("sss.bmp", "wb+");
// 	if (!(bmp = (t_bmp *)calloc(1, sizeof(t_bmp))))
// 		return (ft_output(cub->errno, exit_error(cub, "Nood 3la slaamtek!")));

// 	uint8_t *pixelbuffer = (uint8_t *)malloc(PIXELBYTESIZE);
// 	bmp->header.type[0] = 'B'; bmp->header.type[1] = 'M';
// 	bmp->header.filesize = FILESIZE;
// 	bmp->header.offset = sizeof(bmp);
// 	bmp->info.headersize = sizeof(t_bmpinfo);
// 	bmp->info.width = WIN_WIDTH;
// 	bmp->info.height = WIN_HEIGHT;
// 	bmp->info.planes = PLANES;
// 	bmp->info.bpp = BITSPERPIXEL;
// 	bmp->info.compression = COMPRESSION;
// 	bmp->info.imgsize = PIXELBYTESIZE;
// 	bmp->info.ypixelpmeter = YPIXELPERMETER;
// 	bmp->info.xpixelpmeter = XPIXELPERMETER;
// 	bmp->info.numclrpalette = 0;
// 	bmp->info.mostimpclr = 0;
// 	//write(fd, bmp, sizeof(bmp));
// 	fwrite(bmp, 1, sizeof(t_bmp), fp);
// 	memset(pixelbuffer, 0x0000FF, PIXELBYTESIZE);
// 	fwrite(pixelbuffer, 1, PIXELBYTESIZE, fp);
// 	//write(fd, pixelbuffer, PIXELBYTESIZE);
// 	fclose(fp);
// 	free(bmp);
// 	free(pixelbuffer);
// 	return (SUCCESS);
// }