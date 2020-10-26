#include "../include/cubengine.h"


int		find_checkpoint(t_cub *cub, t_checkpnt *cp, char current_cp)
{
	int		i;
	int		j;
	t_bool	found;

	j = -1;
	found = FALSE;
	while (++j < cub->rows_nb)
	{
		i = -1;
		while (++i < cub->map[j].columns)
		{
			if (cub->map[j].row[i] == current_cp)
			{
				if (found)
					return (exit_error(cub, "Error: Duplicate checkpoint!"));
				found = TRUE;
				cp->name = current_cp;
				cp->x = (i + 0.5F) * TILE_SIZE;
				cp->y = (j + 0.5F) * TILE_SIZE;
			}
		}	
	}
	return (!found ? 0 : 1);
}

int		init_checkpoints(t_cub *cub)
{
	char	current_cp;
	int		retcode;
	int		i;

	i = 0;
	current_cp = 'a';
	while (current_cp <= 't')
	{
		retcode = find_checkpoint(cub, &cub->checkps[i++], current_cp);
		if (IS_ERROR(retcode))
			return (ERROR);
		if (retcode == 0)
			break ;
		++cub->cp_nb;
		cub->lastcpn = current_cp++;
	}
	return (0);
}

int		init_first_level(t_cub *cub)
{
	cub->level[0].start.name = '0';
	cub->level[0].start.x = cub->cam.x;
	cub->level[0].start.y = cub->cam.y;
	cub->level[0].end = cub->checkps[0];
	return (SUCCESS);
}

int		jump_to_level(t_cub *cub, int nextlvl)
{
	// set new splashscreen
	// g_indx_splsh = ...
	g_end_splsh = FALSE;
	cub->cam.x = cub->level[nextlvl].start.x;
	cub->cam.y = cub->level[nextlvl].start.y;
	return (SUCCESS);
}

int		update_level(t_cub *cub)
{
	// cub->currlvl - cub->currcp - cub->lastcpn
	if (cub->currlvl >= cub->level_nb ||
		cub->level[cub->currlvl].end.name >= cub->lastcpn)
		return (SUCCESS);
	if (value_at(cub, floorf(cub->cam.x / TILE_SIZE), floorf(cub->cam.y / TILE_SIZE)) 
		== cub->level[cub->currlvl].end.name)
		jump_to_level(cub, ++cub->currlvl);
	return (SUCCESS);
}

int		init_levels(t_cub *cub)
{
	int			i;
	int			j;
	t_checkpnt 	start;

	i = 0;
	j = 0;
	if (IS_ERROR(init_checkpoints(cub)))
		return (ERROR);
	g_indx_splsh = 0;
	cub->currcp = 0;
	cub->currlvl = 0;
	cub->level_nb = ceilf((cub->cp_nb + 1) / 2.0F);
	init_first_level(cub);
	while (++i < cub->level_nb)
	{
		if (++j < cub->cp_nb)
			cub->level[i].start = cub->checkps[j];
		if (++j < cub->cp_nb)
			cub->level[i].end = cub->checkps[j];
		else
			cub->level[i].end.name = 'z';
	}
	return (SUCCESS);
}