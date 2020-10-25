#include "../include/cubengine.h"

int		event_key_pressed(int key, t_cub *cub)
{
	// ft_putnbr(key);
	// printf("\n");
	if (key == 13 || key == 119)
		cub->cam.mov_dir = 1;
	if (key == 1 || key == 115)
		cub->cam.mov_dir = -1;
	if (key == 124 || key == 65363)
		cub->cam.rot_dir = 1;
	if (key == 123 || key == 65361)
		cub->cam.rot_dir = -1;
	if (key == 0)
	{
		cub->cam.mov_dir = 1;
		cub->cam.side_ang = RAD(-90.0F);
	}
	if (key == 2)
	{
		cub->cam.mov_dir = 1;
		cub->cam.side_ang = RAD(90.0F);
	}
	if (key == 36 && !g_end_splsh)
		g_end_splsh = TRUE;
	return (0);
}

int		event_key_released(int key, t_cub *cub)
{
	if (key == 13 || key == 119)
		cub->cam.mov_dir = 0;
	if (key == 1 || key == 115)
		cub->cam.mov_dir = 0;
	if (key == 124 || key == 65363)
		cub->cam.rot_dir = 0;
	if (key == 123 || key == 65361)
		cub->cam.rot_dir = 0;
	if (key == 0)
	{
		cub->cam.mov_dir = 0;
		cub->cam.side_ang = RAD(0.0F);
	}
	if (key == 2)
	{
		cub->cam.mov_dir = 0;
		cub->cam.side_ang = RAD(0.0F);
	}
	return (0);
}

int		event_game_loop(t_cub *cub)
{
	int		index = SPLSH;
	update_camera(cub);
	update_rays(cub);
	update_rendering_walls(cub);
	update_rendering_sprites(cub);
	if (g_end_splsh)
		index = HUD;
	update_rendering_hud(cub, &cub->txt[index]);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->cnvs.img, 0, 0);
	return (SUCCESS);
}
