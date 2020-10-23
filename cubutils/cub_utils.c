#include "../include/cubengine.h"

int		free_2d(t_str *str)
{
	int		i;

	i = 0;
	while (str[i] != NULL)
		free(str[i++]);
	free(str);
	return (SUCCESS);
}

int		ft_strlen_2d(t_str *str)
{
	int 	i;

	i = 0;
	while (str && str[i] != NULL)
		i++;
	return (i);
}

int		exit_error(t_cub *cub, t_str error_msg)
{
	if (error_msg)
		cub->errno = error_msg;
	return (ERROR);
}

void	draw(t_img *canvas, int x, int y, int color)
{
    canvas->data[y * canvas->width + x] = color;
}

char	value_at(t_cub *cub, int x, int y)
{
	if ((y >= 0 && y < cub->rows_nb) && (x >= 0 && x < cub->map[y].columns))
		return (cub->map[y].row[x]);
	return (' ');
}

t_bool	is_wall(t_cub *cub, int i, int j)
{
	return (value_at(cub, i, j) == '1' ||
			value_at(cub, i, j) == ' ');
}

float	normalize_rad(float angle)
{
	const float two_pi = 2 * M_PI;

	angle = remainderf(angle, two_pi);
	if (angle < 0)
		angle += two_pi;
	return (angle);
}

float	get_distance(t_cub *cub, float x, float y)
{
	return (sqrtf(POW(x - cub->cam.x) + POW(y - cub->cam.y)));
}

int		color_rgb_to_hex(t_color clr)
{
	return ((clr.r * POW(256)) + (clr.g * 256) + clr.b);
}

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

