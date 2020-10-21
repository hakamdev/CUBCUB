#include "../include/cubengine.h"
#include "../include/get_next_line.h"

char	value_at(t_cub *cub, int x, int y)
{
	if ((y >= 0 && y < cub->rows) && (x >= 0 && x < cub->map[y].columns))
		return (cub->map[y].row[x]);
	return (' ');
}

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

int		read_resolution(t_cub *cub, t_str line)
{
	t_str	*split;

	if (ft_strlen_2d((split = ft_split(line, ' '))) < 3)
		return (exit_error(cub, "Error: Width or Height are not provided!"));
	if (ft_strlen_2d(split) > 3)
		return (exit_error(cub, "Error: Only Width and Height are required!"));
	cub->cnvs.width = ft_atoi(split[1]);
	cub->cnvs.height = ft_atoi(split[2]);
	if (cub->cnvs.width == 0 || cub->cnvs.height == 0)
		return (exit_error(cub, "Error: Only Digital, Non-zero values are accepted!"));
	cub->cnvs.width = cub->cnvs.width > 2560 ? 2560 : cub->cnvs.width;
	cub->cnvs.height = cub->cnvs.height > 1395 ? 1395 : cub->cnvs.height;
	free(line);
	cub->read_nb++;
	return (free_2d(split));
}

int		read_xpm(t_cub *cub, t_str line, int txt_index)
{
	t_str	*split;

	if (ft_strlen_2d((split = ft_split(line, ' '))) < 2)
		return (exit_error(cub, "Error: The XPM path is not provided!"));
	if (ft_strlen_2d(split) > 2)
		return (exit_error(cub, "Error: Only one XPM path per line is required!"));
	if (IS_ERROR(check_filename(split[1], EXT_XPM)))
		return (exit_error(cub, "Error: File is not supported, provide a .xpm file!"));
	cub->txt[txt_index].path = ft_strdup(split[1]);
	free(line);
	cub->read_nb++;
	return (free_2d(split));
}

int		check_color(t_color color)
{
	if ((color.r < 0 || color.r > 255)
		|| (color.g < 0 || color.g > 255)
		|| (color.b < 0 || color.b > 255))
		return (ERROR);
	return (SUCCESS);
}

int		read_color(t_cub *cub, t_str line, int clr_index)
{
	t_str	*split;
	int		skip;

	skip = 0;
	while (!(line[skip] >= '0' && line[skip] <= '9') && line[skip] != '-')
		skip++;
	if(ft_strlen_2d((split = ft_split(&line[skip], ','))) < 3)
		return (exit_error(cub, "Error: Missing color values, 3 (R,G,B) are required! or Bad Delim!"));
	if (ft_strlen_2d(split) > 3)
		return (exit_error(cub, "Error: Only 3 (R,G,B) values are required!"));
	cub->color[clr_index].r = ft_atoi(split[0]);
	cub->color[clr_index].g = ft_atoi(split[1]);
	cub->color[clr_index].b = ft_atoi(split[2]);
	if (IS_ERROR(check_color(cub->color[clr_index])))
		return (exit_error(cub, "Error: Color values should be between 0 - 255!"));
	free(line);
	cub->read_nb++;
	return (free_2d(split));
}

int		check_map_element(int i, int j)
{
	int		m;
	int		n;

	n = -2;
	while (++n <= 1)
	{
		m = -2;
		while (++m <= 1)
		{
			if (ft_value_at(i + m, j + n) == ' ')
				return (ERROR);
		}
	}
	return (SUCCESS);
}

int		check_map(t_cub *cub)
{
	int		i;
	int		j;

	j = -1;
	while (++j < cub->rows)
	{
		i = -1;
		while (++i < cub->map[j].columns)
		{
			if (!(ft_value_at(i, j) == '1' || ft_value_at(i, j) == ' ') 
				&& IS_ERROR(check_at(i, j)))
				return (exit_error(cub, "Error: Map is not properly closed!"));
		}
	}
	return (SUCCESS);
}

int		read_map(t_cub *cub, t_str line)
{
	if (cub->read_nb != MAX_READ_CONFIG)
		return (exit_error(cub, "Error: Missing configurations or missplaced map rows!"));
	
	free(line);
	return (SUCCESS);
}

int		handle_line(t_cub *cub, t_str line)
{
	if (IS_SUCESS(ft_strncmp(line, "R ", 2)))
		return (read_resolution(cub, line));
	if (IS_SUCESS(ft_strncmp(line, "NO", 2)))
		return (read_xpm(cub, line, NORTH));
	if (IS_SUCESS(ft_strncmp(line, "SO", 2)))
		return (read_xpm(cub, line, SOUTH));
	if (IS_SUCESS(ft_strncmp(line, "WE", 2)))
		return (read_xpm(cub, line, WEST));
	if (IS_SUCESS(ft_strncmp(line, "EA", 2)))
		return (read_xpm(cub, line, EAST));
	if (IS_SUCESS(ft_strncmp(line, "S ", 2)))
		return (read_xpm(cub, line, SPR));
	if (IS_SUCESS(ft_strncmp(line, "F ", 2)))
		return (read_color(cub, line, FLOOR));
	if (IS_SUCESS(ft_strncmp(line, "C ", 2)))
		return (read_color(cub, line, CIEL));
	if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
		return (read_map(cub, line));
	return (SUCCESS);
}

int		ft_init_read(t_cub *cub)
{
	int		map_fd;
	int		retcode;
	char	*line;

	if (IS_ERROR(map_fd = open(cub->fname, O_RDONLY)))
		return (exit_error(cub, "Error: File doesn't exist!"));
	while ((retcode = get_next_line(map_fd, &line)) > 0)
		if (IS_ERROR(handle_line(cub, line)))
			return (ERROR);
	if (IS_ERROR(retcode))
		return(exit_error(cub, "Error: Cannot read from file!"));
	if (IS_ERROR(handle_line(cub, line)))
		return (ERROR);
	if (IS_ERROR(close(map_fd)))
		return (exit_error(cub, "Error: Failed to close file after read!"));
	return (SUCCESS);
}