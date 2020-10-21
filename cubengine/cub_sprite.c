#include "../include/cubengine.h"

void sort_sprite(t_cub *cub)
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





