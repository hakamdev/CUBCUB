#include "../include/cubengine.h"

float	normalize_rad(float angle)
{
	const float two_pi = 2 * M_PI;

	angle = remainderf(angle, two_pi);
	if (angle < 0)
		angle += two_pi;
	return (angle);
}

float	get_distance(t_cub *cub, float x, float y)
{
	return (sqrtf(POW(x - cub->cam.x) + POW(y - cub->cam.y)));
}
