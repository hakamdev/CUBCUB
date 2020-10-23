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
	update_walls_rendering(cub);
	update_sprites_rendering(cub);
	update_hud_rendering(cub, &cub->txt[HUD]);
	return (SUCCESS);
}
