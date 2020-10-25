#include "../include/cubengine.h"

int		event_key_pressed(int key, t_cub *cub)
{
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
	update_camera(cub);
	update_rays(cub);
	update_rendering_walls(cub);
	update_rendering_sprites(cub);
	update_rendering_hud(cub, &cub->txt[HUD]);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->cnvs.img, 0, 0);
	return (SUCCESS);
}
