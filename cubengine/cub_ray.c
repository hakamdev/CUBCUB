#include "../include/cubengine.h"

void	init_ray(t_ray *ray)
{
		ray->dir[SOUTH] = (ray->ang > 0.0F) && (ray->ang < M_PI);
		ray->dir[EAST] = (ray->ang < M_PI_2) || (ray->ang > (M_PI + M_PI_2));
		ray->dir[NORTH] = !(ray->dir[SOUTH]);
		ray->dir[WEST] = !(ray->dir[EAST]);
}

void	hori_collision(t_cub *cub, t_rdata *h, t_ray *r)
{
	h->inter[Y] = floorf(cub->cam.y / (float)TILE_SIZE) * TILE_SIZE;
	h->inter[Y] += r->dir[SOUTH] ? TILE_SIZE : 0;
	h->inter[X] = cub->cam.x + (h->inter[Y] - cub->cam.y) / tanf(r->ang);
	h->step[Y] = TILE_SIZE;
	h->step[Y] *= r->dir[NORTH] ? -1 : 1;
	h->step[X] = TILE_SIZE / tanf(r->ang);
	h->step[X] *= (r->dir[WEST] && h->step[X] > 0.0F) ? -1 : 1;
	h->step[X] *= (r->dir[EAST] && h->step[X] < 0.0F) ? -1 : 1;
	h->hit[X] = h->inter[X];
	h->hit[Y] = h->inter[Y];
	while (h->hit[Y] >= 0.0F && h->hit[X] >= 0.0F)
	{
		if (is_wall(cub, h->hit[X] / TILE_SIZE,
						(r->dir[NORTH] ? h->hit[Y] - 1 : h->hit[Y]) / TILE_SIZE))
		{
			h->dist = get_distance(cub, h->hit[X], h->hit[Y]);
			break ;
		}
		h->hit[X] += h->step[X];
		h->hit[Y] += h->step[Y];
	}
}

void	vert_collision(t_cub *cub, t_rdata *v, t_ray *r)
{
	v->inter[X] = floorf(cub->cam.x / (float)TILE_SIZE) * TILE_SIZE;
	v->inter[X] += r->dir[SOUTH] ? TILE_SIZE : 0;
	v->inter[Y] = cub->cam.y + (v->inter[X] - cub->cam.x) / tanf(r->ang);
	v->step[X] = TILE_SIZE;
	v->step[X] *= r->dir[NORTH] ? -1 : 1;
	v->step[Y] = TILE_SIZE / tanf(r->ang);
	v->step[Y] *= (r->dir[WEST] && v->step[Y] > 0.0F) ? -1 : 1;
	v->step[Y] *= (r->dir[EAST] && v->step[Y] < 0.0F) ? -1 : 1;
	v->hit[Y] = v->inter[Y];
	v->hit[X] = v->inter[X];
	while (v->hit[Y] >= 0.0F && v->hit[X] >= 0.0F)
	{
		if (is_wall(cub, (r->dir[WEST] ? v->hit[X] - 1 : v->hit[X], v->hit[Y])
						, v->hit[Y]))
		{
			v->dist = get_distance(cub, v->hit[X], v->hit[Y]);
			break ;
		}
		v->hit[X] += v->step[X];
		v->hit[Y] += v->step[Y];
	}
}

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
