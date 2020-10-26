#include "../include/cubengine.h"

int		init_find_inmap(t_cub *cub, int id)
{
	int		i;
	int		j;

	j = -1;
	while (++j < cub->rows_nb)
	{
		i = -1;
		while (++i < cub->map[j].columns)
		{
			if (cub->map[j].row[i] == cub->checkps[id].name)
			{
				cub->checkps[id].x = (i + 0.5F) * TILE_SIZE;
				cub->checkps[id].y = (j + 0.5F) * TILE_SIZE;
				return (SUCCESS);
			}
		}
	}
	return (ERROR);
}

int		init_checkpoints(t_cub *cub)
{
	char	init_char;
	// int		previous_cp;
	// int		current_cp;
	int		i;

	i = -1;
	cub->cp_nb = 0;
	init_char = 'A';
	// current_cp = A;
	while (++i < 7)
	{
		cub->checkps[i].name = init_char++;
		if (IS_ERROR(init_find_inmap(cub, i)))
			break ;
		cub->cp_nb++;
	}
}

int		init_levels(t_cub *cub)
{
	int			i;
	int			j;
	t_checkpnt 	init;

	i = 0;
	j = 0;
	if (cub->cp_nb > 0)
	{
		init.name = '0';
		init.x = cub->cam.x;
		init.y = cub->cam.y;
		cub->level[i].start = init;
		cub->level[i].end = cub->checkps[j];
		i++;
	}
	while (j < cub->cp_nb)
	{
		cub->level[i].start = cub->checkps[j++];
		cub->level[i].end = cub->checkps[j++];
		i++;
	}
	
}