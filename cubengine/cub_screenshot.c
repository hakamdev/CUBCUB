#include "../include/cubengine.h"
#include "../include/get_next_line.h"

int		take_screenshot(t_cub *cub)
{
	int fd;
	t_bmp *bmp;

	
	if (!(fd = open("screenshot.bmp", O_WRONLY | O_APPEND)))
		return (ft_output(cub->errno, exit_error(cub, "Nood 3la slaamtek!")));
	
	if (!(bmp = (t_bmp *)calloc(1, sizeof(t_bmp))))
		return (ft_output(cub->errno, exit_error(cub, "Nood 3la slaamtek!")));

	unsigned char *pixelbuffer = (unsigned char *)malloc((WIN_HEIGHT*WIN_WIDTH*24/8));

	bmp->header.type[0] = 'B'; bmp->header.type[1] = 'M';
	bmp->header.filesize = (WIN_HEIGHT*WIN_WIDTH*24/8)+sizeof(bmp);
	bmp->header.offset = sizeof(bmp);
	bmp->info.headersize = sizeof(t_bmpinfo);
	bmp->info.width = WIN_WIDTH;
	bmp->info.height = WIN_HEIGHT;
	bmp->info.planes = 1;
	bmp->info.bpp = 24;
	bmp->info.compression = 0;
	bmp->info.imgsize = (WIN_HEIGHT*WIN_WIDTH*24/8);
	bmp->info.ypixelpmeter = 0x130B;
	bmp->info.xpixelpmeter = 0x130B;
	bmp->info.numclrpalette = 0;
	write(fd, bmp, sizeof(bmp));
	memset(pixelbuffer, 0xFF, (WIN_HEIGHT*WIN_WIDTH*24/8));
	write(fd, pixelbuffer, (WIN_HEIGHT*WIN_WIDTH*24/8));
	close(fd);
	return (SUCCESS);
}