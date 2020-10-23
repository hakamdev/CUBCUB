#include "../include/cubengine.h"

int		set_camera_rotation(t_cub *cub, char direction)
{
	if (direction == 'N')
		cub->cam.ang = RAD(270);
	else if (direction == 'W')
		cub->cam.ang = RAD(180);
	else if (direction == 'S')
		cub->cam.ang = RAD(90);
	else if (direction == 'E')
		cub->cam.ang = RAD(0);
	return (SUCCESS);
}

t_bool	is_camera(t_cub *cub, int i, int j)
{
	if (value_at(cub, i, j) == 'N' ||
		value_at(cub, i, j) == 'S' ||
		value_at(cub, i, j) == 'W' ||
		value_at(cub, i, j) == 'E')
		return (TRUE);
	return (FALSE);
}
