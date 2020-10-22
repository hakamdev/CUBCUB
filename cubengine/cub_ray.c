#include "../include/cubengine.h"

int		init_rays(t_cub *cub)
{
	int		i;

	i = -1;
	if (!(cub->ray = malloc(sizeof(t_ray) * WIN_WIDTH)))
		return (ERROR);
	while (++i < WIN_WIDTH)
	{
		cub->ray[i].dist = 0.0F;
		cub->ray[i].hit[X] = 0.0F;
		cub->ray[i].hit[Y] = 0.0F;
		cub->ray[i].hitver = FALSE;
		init_ray(&cub->ray[i]);
	}
	return (SUCCESS);
}

void	init_ray(t_ray *ray)
{
		ray->dir[SOUTH] = (ray->ang > 0.0F) && (ray->ang < M_PI);
		ray->dir[EAST] = (ray->ang < M_PI_2) || (ray->ang > (M_PI + M_PI_2));
		ray->dir[NORTH] = !(ray->dir[SOUTH]);
		ray->dir[WEST] = !(ray->dir[EAST]);
}

void	hori_collision(t_cub *cub, t_rdata *h, t_ray *r)
{
	h->dist = INT32_MAX;
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
		if (is_wall(/* TODO */))
		{
			h->dist = get_distance();
		}
	}
	
}

void	vert_collision(t_cub *cub, t_rdata *v, t_ray *r)
{

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