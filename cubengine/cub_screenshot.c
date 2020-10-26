#include "../include/cubengine.h"
#include "../include/get_next_line.h"

int		take_screenshot(t_cub *cub)
{
	int fd;
	t_bmp *bmp;

	
	// if (!(fd = open("ss.bmp", O_CREAT | O_RDWR | O_APPEND)))
	// 	return (ft_output(cub->errno, exit_error(cub, "Nood 3la slaamtek!")));
	
	FILE *fp = fopen("sss.bmp", "wb+");
	if (!(bmp = (t_bmp *)calloc(1, sizeof(t_bmp))))
		return (ft_output(cub->errno, exit_error(cub, "Nood 3la slaamtek!")));

	uint8_t *pixelbuffer = (uint8_t *)malloc(PIXELBYTESIZE);
	bmp->header.type[0] = 'B'; bmp->header.type[1] = 'M';
	bmp->header.filesize = FILESIZE;
	bmp->header.offset = sizeof(bmp);
	bmp->info.headersize = sizeof(t_bmpinfo);
	bmp->info.width = WIN_WIDTH;
	bmp->info.height = WIN_HEIGHT;
	bmp->info.planes = PLANES;
	bmp->info.bpp = BITSPERPIXEL;
	bmp->info.compression = COMPRESSION;
	bmp->info.imgsize = PIXELBYTESIZE;
	bmp->info.ypixelpmeter = YPIXELPERMETER;
	bmp->info.xpixelpmeter = XPIXELPERMETER;
	bmp->info.numclrpalette = 0;
	bmp->info.mostimpclr = 0;
	//write(fd, bmp, sizeof(bmp));
	fwrite(bmp, 1, sizeof(t_bmp), fp);
	memset(pixelbuffer, 0x0000FF, PIXELBYTESIZE);
	fwrite(pixelbuffer, 1, PIXELBYTESIZE, fp);
	//write(fd, pixelbuffer, PIXELBYTESIZE);
	fclose(fp);
	free(bmp);
	free(pixelbuffer);
	return (SUCCESS);
}