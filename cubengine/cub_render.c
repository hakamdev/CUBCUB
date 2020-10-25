#include "../include/cubengine.h"

void	render_sprite(t_cub *cub, int id, int offx, int offy)
{
	int			x;
	int			y;
	int			rx;
	int			ry;
	int			clrindex;
	const float	ratio = cub->txt[SPR].width / cub->spr[id].scale;
	const int	max = WIN_WIDTH * WIN_HEIGHT;

	x = -1;
	while (++x < (int)cub->spr[id].scale)
	{
		if (offx + x < 0 || offx + x >= WIN_WIDTH)
			continue ;
		if (cub->ray[offx + x].dist <= cub->spr[id].dist)
			continue ;
		y = -1;
		rx = (x * ratio);
		while (++y < (int)cub->spr[id].scale)
		{
			if (offy + y < 0 || offy + y >= WIN_HEIGHT)
				continue ;
			ry = (y * ratio);
			clrindex = (ry * cub->txt[SPR].width) + rx;
			if (cub->txt[SPR].data[clrindex] != 0x980088)
				draw(&cub->cnvs, offx + x, offy + y, cub->txt[SPR].data[clrindex]);
		}
	}
}

// void	render_sprite(t_cub *cub, int id, int offx, int offy)
// {
// 	int			i;
// 	int			j;
// 	int			clr_index;
// 	const int	max = WIN_WIDTH * WIN_HEIGHT;
//
// 	i = -1;
// 	while (++i < (int)cub->spr[id].scale)
// 	{
// 		if (offx + i < 0 || offx + i >= WIN_WIDTH ||
// 			cub->ray[offx + i].dist <= cub->spr[id].dist)
// 			continue ;
// 		j = -1;
// 		while (++j < (int)cub->spr[id].scale)
// 		{
// 			if (offy + j < 0 || offy + j >= WIN_WIDTH)
// 				continue ;
// 			clr_index = TILE_SIZE * (TILE_SIZE * j / (int)cub->spr[id].scale) + (TILE_SIZE * i / (int)cub->spr[id].scale);
// 			clr_index = clr_index >= max ? max : clr_index;
// 			if (cub->txt[SPR].data[clr_index] != 0x980088)
// 				draw(&cub->cnvs, offx + i, offy + j, cub->txt[SPR].data[clr_index]);
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
