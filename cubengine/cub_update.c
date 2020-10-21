#include "../include/cubengine.h"

void		update_camera(t_cub *cub)
{
	float	next_x;
	float	next_y;

	next_x = cub->cam.x + cub->cam.mov_spd * 
			cub->cam.mov_dir * cosf(cub->cam.ang /* TODO */);
	next_y = cub->cam.y + cub->cam.mov_spd * 
			cub->cam.mov_dir * sinf(cub->cam.ang /* TODO */);
	cub->cam.ang = cub->cam.ang + cub->cam.rot_spd * cub->cam.rot_dir;
	/* TODO */
	if (FALSE)
		cub->cam.x = next_x;
	if (FALSE)
		cub->cam.y = next_y;
}