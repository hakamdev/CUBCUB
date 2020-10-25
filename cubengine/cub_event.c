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
	if (key == 0 || key == 97)
	{
		cub->cam.mov_dir = 1;
		cub->cam.side_ang = RAD(-90.0F);
	}
	if (key == 2 || key == 100)
	{
		cub->cam.mov_dir = 1;
		cub->cam.side_ang = RAD(90.0F);
	}
	if ((key == 36 || key == 65293) && !g_end_splsh)
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
	if (key == 0 || key == 97)
	{
		cub->cam.mov_dir = 0;
		cub->cam.side_ang = RAD(0.0F);
	}
	if (key == 2 || key == 100)
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
	if (cub->cam.x >= 64.0F && cub->cam.x <= 128.0F && cub->cam.y >= 768.0F && cub->cam.y <= 832.0F)
	{
		cub->cam.x = 96.0F; cub->cam.y = 1024.0F;
		set_camera_rotation(cub, 'S');
		g_end_splsh = FALSE;
	}
	if (cub->cam.x >= 64.0F && cub->cam.x <= 128.0F && cub->cam.y >= 1664.0F && cub->cam.y <= 1728.0F)
	{
		cub->cam.x = 96.0F; cub->cam.y = 96.0F;
		set_camera_rotation(cub, 'S');
		g_end_splsh = FALSE;
	}
	// y768 - y832 x64 - x128 96 
	return (SUCCESS);
}
