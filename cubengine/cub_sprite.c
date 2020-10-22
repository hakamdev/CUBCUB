#include "../include/cubengine.h"

float	normalize_rad(float angle)
{
	const float two_pi = 2 * M_PI;

	angle = remainderf(angle, two_pi);
	if (angle < 0)
		angle += two_pi;
	return (angle);
}

float	normalize_spr(t_cub *cub, float angle)
{
	while (angle - cub->cam.ang > M_PI)
        angle -= 2 * M_PI;
    while (angle - cub->cam.ang < -M_PI)
        angle += 2 * M_PI;
	return (angle);
}

float	get_distance(t_cub *cub, float x, float y)
{
	return (sqrtf(POW(x - cub->cam.x) + POW(y - cub->cam.y)));
}

void	render_sprite(t_cub *cub, int id, int offx, int offy)
{
	int			i;
	int			j;
	int			clr_index;
	const int	max = cub->cnvs.width * cub->cnvs.height;

	i = -1;
	while (++i < cub->spr[id].scale)
	{
		if (offx + i < 0 || offx + i >= cub->cnvs.width ||
			cub->ray[offx + i].dist <= cub->spr[id].dist)
			continue ;
		j = -1;
		while (++j < cub->spr[id].scale)
		{
			if (offy + j < 0 || offy + j >= cub->cnvs.width)
				continue ;
			clr_index = cub->txt[SPR].width * (cub->txt[SPR].width * j / cub->spr[id].scale) +
												(cub->txt[SPR].width * i / cub->spr[id].scale);
			clr_index = clr_index >= max ? max : clr_index;
			if (cub->txt[SPR].data[clr_index] != 0x980088)
				draw(&cub->cnvs, offx, offy, cub->txt[SPR].data[clr_index]);
		}
	}
}

void	update_sprites(t_cub *cub)
{
	int			i;
	const float	pplane_dist = cub->cnvs.width / 2.0F / tanf(RAD(FOV / 2.0F));;

	i = -1;
	while (++i < cub->sprs_nb)
	{
		cub->spr[i].dist = get_distance(cub, cub->spr[i].x, cub->spr[i].y);
		cub->spr[i].ang = atan2f(cub->spr[i].y - cub->cam.y, cub->spr[i].x - cub->cam.x);
		cub->spr[i].ang = normalize_spr(cub, cub->spr[i].ang);
		cub->spr[i].scale = (TILE_SIZE / (cub->spr[i].dist * pplane_dist));
		cub->spr[i].offy = (cub->cnvs.height / 2.0F) - (cub->spr[i].scale / 2.0F);
		cub->spr[i].offx = ((DEG(cub->spr[i].ang - DEG(cub->cam.ang))) * cub->cnvs.width) / TILE_SIZE +
							((cub->cnvs.width / 2.0F) - (cub->spr[i].scale / 2.0F));
	}
	sort_sprite(cub);
	i = -1;
	while (++i < cub->sprs_nb)
		render_sprite(cub, i, cub->spr[i].offx, cub->spr[i].offy);
}

void	sort_sprites(t_cub *cub)
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
			{
				if (IS_ERROR(add_sprite(cub, i, j)))
					return (cub, "Error: Failed to allocate memory!");
			}
	}
	return (SUCCESS);
}
