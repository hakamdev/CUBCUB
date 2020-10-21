#include "../include/cubengine.h"

void	update_sprite()
{
	
}

void	sort_sprite(t_cub *cub)
{
    int i;
	int	j;
    int sprs_nb;
    t_sprite spr_tmp;

	i = -1;
	sprs_nb = cub->sprs_nb;
    while (++i < cub->sprs_nb)
    {
		j = -1;
        while (++j + 1 < sprs_nb)
            if (cub->spr[j].dist < cub->spr[j + 1].dist)
            {
                spr_tmp = cub->spr[j + 1];
                cub->spr[j + 1] = cub->spr[j];
                cub->spr[j] = spr_tmp;
            }
        --sprs_nb;
    }
}

int		add_sprite(t_cub *cub, int i, int j)
{
	int			index;
	t_sprite	tmp_spr;
	t_sprite	*tmp_sprs;

	tmp_spr.x = (i + 0.5f) * TILE_SIZE;
	tmp_spr.y = (j + 0.5f) * TILE_SIZE;
	if (cub->spr == NULL && !(cub->spr = (t_sprite *)malloc(sizeof(t_sprite) * 1)))
		return (ERROR);
    else
    {
		index = -1;
        tmp_sprs = cub->spr;
        if (!(cub->spr = (t_sprite *)malloc(sizeof(t_sprite) * ++(cub->sprs_nb))))
			return (ERROR);
        while (++index < cub->sprs_nb - 1)
            cub->spr[index] = tmp_sprs[index];
        free(tmp_sprs);
    }
    cub->spr[index] = tmp_spr;
	return (SUCCESS);
}

int		init_sprites(t_cub *cub)
{
	int		i;
	int		j;

	j = -1;
	while (++j < cub->rows_nb)
	{
		i = -1;
		while (++i < cub->map[j].columns)
			if (ft_strnchar("234", value_at(cub, i, j)))
				if (IS_ERROR(add_sprite(cub, i, j)))
					return (cub, "Error: Failed to allocate memory!");
	}
	return (SUCCESS);
}

