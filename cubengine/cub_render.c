#include "../include/cubengine.h"

void	render_sprite(t_cub *cub, int id, int off[2], int spr)
{
	int			x;
	int			y;
	int			rx;
	int			ry;
	int			clrindex;
	const float	ratio = cub->txt[SPR].width / cub->spr[id].scale;

	x = -1;
	while (++x < (int)cub->spr[id].scale)
	{
		if (off[X] + x < 0 || off[X] + x >= WIN_WIDTH)
			continue ;
		if (cub->ray[off[X] + x].dist <= cub->spr[id].dist)
			continue ;
		y = -1;
		// rx = (x * ratio);
		while (++y < (int)cub->spr[id].scale)
		{
			if (off[Y] + y < 0 || off[Y] + y >= WIN_HEIGHT)
				continue ;
			ry = (y * ratio);
			clrindex = (ry * cub->txt[spr].width) + rx;
			if (cub->txt[spr].data[clrindex] != cub->txt[spr].data[0])
				draw(&cub->cnvs, off[X] + x, off[Y] + y, cub->txt[spr].data[clrindex]);
		}
	}
}

// void	render_sprite(t_cub *cub, int id, int offx, int offy)
// {
// 	int			x;
// 	int			y;
// 	int			rx;
// 	int			ry;
// 	int			clrindex;
// 	const float	ratio = cub->txt[SPR].width / cub->spr[id].scale;

// 	x = -1;
// 	while (++x < (int)cub->spr[id].scale)
// 	{
// 		if (offx + x < 0 || offx + x >= WIN_WIDTH)
// 			continue ;
// 		if (cub->ray[offx + x].dist <= cub->spr[id].dist)
// 			continue ;
// 		y = -1;
// 		rx = (x * ratio);
// 		while (++y < (int)cub->spr[id].scale)
// 		{
// 			if (offy + y < 0 || offy + y >= WIN_HEIGHT)
// 				continue ;
// 			ry = (y * ratio);
// 			clrindex = (ry * cub->txt[SPR].width) + rx;
// 			if (cub->txt[SPR].data[clrindex] != cub->txt[SPR].data[0])
// 				draw(&cub->cnvs, offx + x, offy + y, cub->txt[SPR].data[clrindex]);
// 		}
// 	}
// }

void    render_wall_stripe(t_cub *cub, t_wdata *stripe, int x)
{
	int		y;
	int		color;
	int		pos[2];

	y = stripe->top - 1;
	pos[X] = x;
    while (++y < stripe->bttm)
    {
		pos[Y] = y;
        if (cub->ray[x].hitver && cub->ray[x].dir[WEST])
			color = get_color_from_txt(cub, stripe, pos, WEST);
        else if (cub->ray[x].hitver && cub->ray[x].dir[EAST])
			color = get_color_from_txt(cub, stripe, pos, EAST);
		else if (!cub->ray[x].hitver && cub->ray[x].dir[NORTH])
			color = get_color_from_txt(cub, stripe, pos, NORTH);
        else if (!cub->ray[x].hitver && cub->ray[x].dir[SOUTH])
			color = get_color_from_txt(cub, stripe, pos, SOUTH);
		draw(&cub->cnvs, x, y, color);
    }
}

void	render_ciel_stripe(t_cub *cub, int ystart, int yend, int x)
{
	while (ystart < yend)
		draw(&cub->cnvs, x, ystart++, color_rgb_to_hex(cub->color[CIEL]));
}

void	render_flor_stripe(t_cub *cub, int ystart, int yend, int x)
{
	while (ystart < yend)
		draw(&cub->cnvs, x, ystart++, color_rgb_to_hex(cub->color[FLOOR]));
}
