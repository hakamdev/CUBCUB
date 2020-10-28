#include "../include/cubengine.h"

void update_camera(t_cub *cub)
{
	float next_x;
	float next_y;

	next_x = cub->cam.x + cub->cam.mov_spd *
				cub->cam.mov_dir *
				cosf(cub->cam.ang + cub->cam.side_ang) * 20;
	next_y = cub->cam.y + cub->cam.mov_spd *
				cub->cam.mov_dir *
				sinf(cub->cam.ang + cub->cam.side_ang) * 20;
	cub->cam.ang += (cub->cam.rot_spd * cub->cam.rot_dir);
	if (!is_wall(cub, next_x, cub->cam.y) &&
		!is_sprite(cub, next_x, cub->cam.y))
		cub->cam.x = next_x;
	if (!is_wall(cub, cub->cam.x, next_y) &&
		!is_sprite(cub, cub->cam.x, next_y))
		cub->cam.y = next_y;
}

void update_rays(t_cub *cub)
{
	int i;
	float start_ang;
	const float ang_step = FOV / WIN_WIDTH;
	t_ray	*rrr;

	i = -1;
	start_ang = cub->cam.ang - (FOV / 2);
	while (++i < WIN_WIDTH)
	{
		cub->ray[i].ang = normalize_rad(start_ang);
		update_ray(cub, &cub->ray[i]);
		start_ang += ang_step;
		rrr = &cub->ray[i];
	}
}

void update_rendering_walls(t_cub *cub)
{
	int i;
	int j;
	t_wdata strp;
	const float pplane_dist = (WIN_WIDTH / 2.0F) / tanf((FOV) / 2);

	i = -1;
	while (++i < WIN_WIDTH)
	{
		cub->ray[i].dist *= cosf(cub->ray[i].ang - cub->cam.ang);
		strp.height = TILE_SIZE / cub->ray[i].dist * pplane_dist;
		strp.top = ((float)WIN_HEIGHT / 2) - (strp.height / 2);	 /* TODO updown */
		strp.bttm = ((float)WIN_HEIGHT / 2) + (strp.height / 2); /* TODO updown */
		strp.top = strp.top < 0 ? 0 : strp.top;
		strp.bttm = strp.bttm > WIN_HEIGHT ? WIN_HEIGHT : strp.bttm;
		render_ciel_stripe(cub, 0, strp.top, i);
		render_wall_stripe(cub, &strp, i);
		render_flor_stripe(cub, strp.bttm, WIN_HEIGHT, i);
	}
}

int	get_sprite_type(t_cub *cub, int x, int y)
{
	const char c = value_at_pos(cub, x, y);
	if (c >= 'a' && c <= 't')
		return (CP);
	return (SPR);
}

void update_rendering_sprites(t_cub *cub)
{
	int i;
	const float pplane_dist = (WIN_WIDTH / 2.0F) / tanf((FOV) / 2) - 10;

	i = -1;
	int	off[2];

	while (++i < cub->sprs_nb)
	{
		cub->spr[i].dist = get_distance(cub, cub->spr[i].x, cub->spr[i].y);
		cub->spr[i].ang = atan2f(cub->spr[i].y - cub->cam.y,
								 cub->spr[i].x - cub->cam.x);
		cub->spr[i].ang = normalize_spr(cub, cub->spr[i].ang);
		cub->spr[i].scale = (TILE_SIZE / cub->spr[i].dist * pplane_dist);
		cub->spr[i].offy = (WIN_HEIGHT / 2.0F) - (cub->spr[i].scale / 2);
		cub->spr[i].offx = ((DEG(cub->spr[i].ang) - DEG(cub->cam.ang)) * WIN_WIDTH)
	/ (cub->txt[SPR].width) + ((WIN_WIDTH / 2.0F) - (cub->spr[i].scale / 2));
	}
	sort_sprites(cub);
	i = -1;
	while (++i < cub->sprs_nb)
	{
		off[X] = cub->spr[i].offx;
		off[Y] = cub->spr[i].offy;
		render_sprite(cub, i, off, get_sprite_type(cub, cub->spr[i].x, cub->spr[i].y));
	}
}

void update_rendering_hud(t_cub *cub, t_img *hud)
{
	int x;
	int y;
	int rx;
	int ry;

	y = 0;
	ry = 0;
	while (y < WIN_HEIGHT && ry < hud->height)
	{
		x = 0;
		rx = 0;
		while (x < WIN_WIDTH && rx < hud->width)
		{
			if (g_end_splsh && hud->data[(ry * hud->width) + rx] != 0x527052)
				draw(&cub->cnvs, x, y, hud->data[(ry * hud->width) + rx]);
			if (!g_end_splsh)
				draw(&cub->cnvs, x, y, hud->data[(ry * hud->width) + rx]);
			rx = ++x * hud->hratio;
		}
		ry = ++y * hud->vratio;
	}
}
