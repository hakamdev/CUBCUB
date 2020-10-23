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

int		init_camera(t_cub *cub)
{
	t_bool		cam_exists;
	int			i;
	int			j;

	j = -1;
	cam_exists = FALSE;
	while (++j < cub->rows_nb)
	{
		i = -1;
		while (++i < cub->map[j].columns)
		{
			if (is_camera(cub, i, j))
			{
				if (cam_exists)
					return (exit_error(cub, "Error: Only one Player is required!"));
				cam_exists = TRUE;
				set_camera_rotation(cub, value_at(cub, i, j));
				cub->cam.x = (i + 0.5F) * TILE_SIZE;
				cub->cam.y = (j + 0.5F) * TILE_SIZE;
			}
		}
	}
	return (!cam_exists ? 
			exit_error(cub, "Error: Player doesn't exist in Map!") : SUCCESS);
}