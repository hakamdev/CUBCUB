#include "../include/cubengine.h"

void	update_ray(t_cub *cub, t_ray *ray)
{
	t_rdata		horizontal;
	t_rdata		vertical;

	init_ray(ray);
	hori_collision(cub, &horizontal, ray);
	vert_collision(cub, &vertical, ray);
	if (vertical.dist > horizontal.dist)
	{
		ray->hitver = FALSE;
		ray->dist = horizontal.dist;
		ray->hit[X] = horizontal.hit[X];
		ray->hit[Y] = horizontal.hit[Y];
	}
	else
	{
		ray->hitver = TRUE;
		ray->dist = vertical.dist;
		ray->hit[X] = vertical.hit[X];
		ray->hit[Y] = vertical.hit[Y];
	}
}

void	update_rays(t_cub *cub)
{
	int			i;
	float		start_ang;
	const float	angle_step = FOV / WIN_WIDTH;

	i = -1;
	start_ang = cub->cam.ang - (FOV / 2);
	while (++i < WIN_WIDTH)
	{
		cub->ray[i].ang = normalize_rad(start_ang);
		update_ray(cub, &cub->ray[i]);
		start_ang += angle_step;
	}
}

void	update_camera(t_cub *cub)
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

void	update_sprites_rendering(t_cub *cub)
{
	int			i;
	const float	pplane_dist = WIN_WIDTH / 2.0F / tanf(RAD(FOV / 2.0F));;

	i = -1;
	while (++i < cub->sprs_nb)
	{
		cub->spr[i].dist = get_distance(cub, cub->spr[i].x, cub->spr[i].y);
		cub->spr[i].ang = atan2f(cub->spr[i].y - cub->cam.y, cub->spr[i].x - cub->cam.x);
		cub->spr[i].ang = normalize_spr(cub, cub->spr[i].ang);
		cub->spr[i].scale = (TILE_SIZE / (cub->spr[i].dist * pplane_dist));
		cub->spr[i].offy = (WIN_HEIGHT / 2.0F) - (cub->spr[i].scale / 2.0F);
		cub->spr[i].offx = ((DEG(cub->spr[i].ang - DEG(cub->cam.ang))) * WIN_WIDTH) / TILE_SIZE +
							((WIN_WIDTH / 2.0F) - (cub->spr[i].scale / 2.0F));
	}
	sort_sprite(cub);
	i = -1;
	while (++i < cub->sprs_nb)
		render_sprite(cub, i, cub->spr[i].offx, cub->spr[i].offy);
}

void	update_walls_rendering(t_cub *cub)
{
	int		i;
	int		j;
	float	pplane_dist;
	t_wdata	strp;

	i = -1;
	pplane_dist	= (WIN_WIDTH / 2.0F) / tanf((FOV) / 2);
	while (++i < WIN_WIDTH)
	{
		cub->ray[i].dist *= cosf(cub->ray[i].ang - cub->cam.ang);
		strp.height = TILE_SIZE / cub->ray[i].dist * pplane_dist;
		strp.top = ((float)WIN_HEIGHT / 2) - (strp.height / 2); /* TODO updown */
		strp.bttm = ((float)WIN_HEIGHT / 2) + (strp.height / 2); /* TODO updown */
		render_ciel_stripe(cub, 0, strp.top, i);
		render_wall_stripe(cub, &strp, i);
		render_flor_stripe(cub, strp.bttm, WIN_HEIGHT, i);
	}
}