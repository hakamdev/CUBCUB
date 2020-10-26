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
			else if (!ft_strnchar("012NEWS abcdefghijklmnopqrst", value_at(cub, i, j)))
				return (exit_error(cub, "Error: Fobidden character exist in map!"));
		}
	}
	return (SUCCESS);
}

int		check_args( t_cub *cub, int argc, const t_str *args)
{
	if (argc < 2)
		return (exit_error(cub, "Error: At least 1 argument is required!"));
	if (argc > 3)
		return (exit_error(cub, "Error: Too many arguments!"));
	if (IS_ERROR(check_filename(args[1], EXT_CUB)))
		return (exit_error(cub, "Error: File is not supported, provide .cub file!"));
	cub->fname = args[1];
	if (argc == 3 && IS_SUCESS(ft_strncmp(args[2], "--save", 6)))
		cub->screenshot = TRUE;
	else if (argc == 3)
		return (exit_error(cub, "Error: 2nd argument is not recognized!"));
	return (SUCCESS);
}
