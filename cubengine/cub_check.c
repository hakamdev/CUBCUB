#include "../include/cubengine.h"

int		check_filename(t_str filename, int ext)
{
	int		len;

	len = ft_strlen(filename);
	if (IS_SUCESS(ft_strncmp(&filename[len - 4], 
					ext == EXT_CUB ? ".cub" : ".xpm", 6)))
		return (SUCCESS);
	return (ERROR);
}

int		check_color(t_color color)
{
	if ((color.r < 0 || color.r > 255)
		|| (color.g < 0 || color.g > 255)
		|| (color.b < 0 || color.b > 255))
		return (ERROR);
	return (SUCCESS);
}

int		check_map_element(t_cub *cub, int i, int j)
{
	int		m;
	int		n;

	n = -2;
	while (++n <= 1)
	{
		m = -2;
		while (++m <= 1)
			if (value_at(cub, i + m, j + n) == ' ')
				return (ERROR);
	}
	return (SUCCESS);
}

int		check_map(t_cub *cub)
{
	int		i;
	int		j;

	j = -1;
	while (++j < cub->rows_nb)
	{
		i = -1;
		while (++i < cub->map[j].columns)
		{
			if (ft_strnchar("02NEWS", (value_at(cub, i, j)))
				&& IS_ERROR(check_map_element(cub, i, j)))
				return (exit_error(cub, "Error: Map is not properly closed!"));
			else if (!ft_strnchar("012NEWS ", value_at(cub, i, j)))
				return (exit_error(cub, "Error: Fobidden character exist in map!"));
		}
	}
	return (SUCCESS);
}


