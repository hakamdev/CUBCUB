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

void	hori_collision(t_rdata *rd, t_ray *ray, int ax1, int ax2)
{
	rd->dist = INT32_MAX;
	//rd->inter[ax1] = floorf()
}

void	vert_collision(t_rdata *ver, t_ray *ray)
{

}

void	update_ray(t_ray *ray)
{
	t_rdata		horizontal;
	t_rdata		vertical;

	init_ray(ray);
	hori_collision(&horizontal, ray);
	vert_collision(&vertical, ray);
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
		update_ray(&cub->ray[i]);
		start_ang += angle_step;
	}
}