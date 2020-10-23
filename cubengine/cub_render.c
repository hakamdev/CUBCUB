#include "../include/cubengine.h"

int		get_color_from_txt(t_cub *cub, t_wdata *stripe, int pos[2], int img)
{
	int			off[2];
	float		vertoff;
	const int	x = pos[X];
	const int	y = pos[Y];

	vertoff = y + (stripe->height - WIN_HEIGHT) / 2; /*TODO updown */
	off[X] = (int)(cub->ray[x].hitver ? cub->ray[x].hit[Y] :
					cub->ray[x].hit[X]) % cub->txt[img].height;
	off[Y] = vertoff * (cub->txt[img].height / stripe->height);
	off[X] = off[X] < 0 ? 0 : off[X];
	off[Y] = off[Y] < 0 ? 0 : off[Y];
	return (cub->txt[img].data[(off[Y] * cub->txt[img].width) + off[X]]);
}

void    render_hud(t_cub *cub)
{

}

void    render_wall_stripe(t_cub *cub, t_wdata *stripe, int x)
{
	int		color;
	int		y;
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
