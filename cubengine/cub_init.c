#include "../include/cubengine.h"
#include "../include/get_next_line.h"

int		init_read(t_cub *cub)
{
	int		map_fd;
	int		retcode;
	char	*line;

	if (IS_ERROR(map_fd = open(cub->fname, O_RDONLY)))
		return (exit_error(cub, "Error: File doesn't exist!"));
	while ((retcode = get_next_line(map_fd, &line)) > 0)
		if (IS_ERROR(handle_line(cub, line)))
			return (ERROR);
	if (IS_ERROR(retcode))
		return(exit_error(cub, "Error: Cannot read from file!"));
	if (IS_ERROR(handle_line(cub, line)))
		return (ERROR);
	if (IS_ERROR(close(map_fd)))
		return (exit_error(cub, "Error: Failed to close file after read!"));
	if (IS_ERROR(check_map(cub)))
		return (ERROR);
	return (SUCCESS);
}

int		init_mlx(t_cub *cub)
{
	if (!(cub->mlx = mlx_init()))
		return (exit_error(cub, "Error: Failed to initialize mlx!"));
	if (!(cub->window = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, CUBTITLE)))
		return (exit_error(cub, "Error: Failed to initialize window!"));
	if (!(cub->cnvs.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT)))
		return (exit_error(cub, "Error: Failed to initialize Canvas!"));
	cub->cnvs.data = (int *)mlx_get_data_addr(cub->cnvs.img, &cub->cnvs.bpp,
											&cub->cnvs.sl, &cub->cnvs.end);
	return (SUCCESS);
}

int		init_cam(t_cub *cub)
{
	cub->cam.mov_dir =		0;
	cub->cam.rot_dir =		0;
	cub->cam.side_ang = 	0.0F;
	cub->cam.mov_spd = 		(TILE_SIZE / 60.0F);
	cub->cam.rot_spd =		RAD(1.2F);
	return (SUCCESS);
}

int		init_cub(t_cub *cub)
{
	int		i;

	i =						-1;
	cub->cam.x =			-1;
	cub->cam.y =			-1;
	cub->read_nb = 			0;
	cub->sprs_nb = 			0;
	WIN_WIDTH = 			0;
	WIN_HEIGHT = 			0;
	cub->errno =			NULL;
	cub->fname =			NULL;
	cub->screenshot = 		FALSE;
	cub->map = 				NULL;
	cub->spr = 				NULL;
	cub->ray = 				NULL;
	init_cam(cub);
	while (++i < 6)
		cub->txt[i].path =	NULL;
	return (SUCCESS);
}

/* MAIN INITIALIZION FUNCTION */
int		init_game(t_cub *cub, int ac, t_str *av)
{
	init_cub(cub);
	if (IS_ERROR(check_args(cub, ac, av)))
		return (ft_output(cub->errno, ERROR));
	if (IS_ERROR(init_read(cub)))
		return (ft_output(cub->errno, ERROR));
	if (IS_ERROR(init_camera(cub)))
		return (ft_output(cub->errno, ERROR));
	if (IS_ERROR(init_mlx(cub)))
		return (ft_output(cub->errno, ERROR));
	if (IS_ERROR(init_textures(cub)))
		return (ft_output(cub->errno, ERROR));
	if (IS_ERROR(init_rays(cub)))
		return (ft_output(cub->errno, ERROR));
	if (IS_ERROR(init_sprites(cub)))
		return (ft_output(cub->errno, ERROR));
	//if (IS_ERROR(init_levels(cub)))
	//	return (ft_output(cub->errno, ERROR));
	return (SUCCESS);
}

