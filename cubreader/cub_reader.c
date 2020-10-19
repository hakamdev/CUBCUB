#include "../include/cubengine.h"
#include "../include/get_next_line.h"

int		init_read(t_cub *cub)
{
	int		map_fd;

	map_fd = open(cub->fname, O_RDONLY);
	if (IS_ERROR(map_fd))
		return (exit_error(cub, "Error: File doesn't exist!"));
}