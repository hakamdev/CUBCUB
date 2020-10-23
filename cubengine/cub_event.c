#include "../include/cubengine.h"

int		event_key_pressed(int key, t_cub *cub)
{

}

int		event_key_released(int key, t_cub *cub)
{

}

int		event_game_loop(t_cub *cub) 
{
	update_camera(cub);
	update_rays(cub);
	update_rendering_walls(cub);
	update_rendering_sprites(cub);
	update_rendering_hud(cub, &cub->txt[HUD]);
	return (SUCCESS);
}
