#include "../include/cubengine.h"

int		event_key_pressed(int key, t_cub *cub)
{
	if (key == 13)
		cub->cam.mov_dir = 1;
	if (key == 1)
		cub->cam.mov_dir = -1;
	if (key == 124)
		cub->cam.rot_dir = 1;
	if (key == 123)
		cub->cam.rot_dir = -1;
	return (0);
}

int		event_key_released(int key, t_cub *cub)
{
	if (key == 13)
		cub->cam.mov_dir = 0;
	if (key == 1)
		cub->cam.mov_dir = 0;
	if (key == 124)
		cub->cam.rot_dir = 0;
	if (key == 123)
		cub->cam.rot_dir = 0;
	return (0);
}

int		event_game_loop(t_cub *cub)
{
	update_camera(cub);
	update_rays(cub);
	update_rendering_walls(cub);
	//update_rendering_sprites(cub);
	//update_rendering_hud(cub, &cub->txt[HUD]);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->cnvs.img, 0, 0);
	return (SUCCESS);
}
