#include "../include/cubengine.h"

int		init_cam(t_cub *cub)
{
	cub->cam.mov_dir =		FALSE;
	cub->cam.rot_dir =		FALSE;
	cub->cam.mov_spd = 		(TILE_SIZE / 20.0F);
	cub->cam.rot_spd =		RAD(1.0F);
	return (SUCCESS);
}

int		init_mlx(t_cub *cub)
{
	if (!(cub->mlx = mlx_init()))
		return (exit_error(cub, "Error: Failed to initialize mlx!"));
	if (!(cub->window = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, CUBTITLE)))
		return (exit_error(cub, "Error: Failed to initialize window!"));
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
	init_cam(cub);
	while (++i < 6)
		cub->txt[i].path =	NULL;
	return (SUCCESS);
}

int		init_game(t_cub *cub, int ac, int av)
{
	init_cub(cub);
	if (IS_ERROR(handle_args(cub, ac, av)))
		return (ft_output(cub->errno, ERROR));
	if (IS_ERROR(init_read(cub)))
		return (ft_output(cub->errno, ERROR));
	if (IS_ERROR(init_camera(cub)))
		return (ft_output(cub->errno, ERROR));
	if (IS_ERROR(init_mlx(cub)))
		return (ft_output(cub->errno, ERROR));
	if (IS_ERROR(init_rays(cub)))
		return (ft_output(cub->errno, ERROR));
	if (IS_ERROR(init_sprites(cub)))
		return (ft_output(cub->errno, ERROR));
	return (SUCCESS);
}

