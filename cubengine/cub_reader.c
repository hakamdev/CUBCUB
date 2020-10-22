#include "../include/cubengine.h"
#include "../include/get_next_line.h"

char	value_at(t_cub *cub, int x, int y)
{
	if ((y >= 0 && y < cub->rows_nb) && (x >= 0 && x < cub->map[y].columns))
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

int		read_map(t_cub *cub, t_str line)
{
	int		i;
	t_map	*tmap;

	if (cub->read_nb != MAX_READ_CONFIG)
		return (exit_error(cub, "Error: Missing configurations or missplaced map rows!"));
	if (cub->map == NULL)
	{
		if(!(cub->map = malloc(1 * sizeof(t_map))))
		return (exit_error(cub, "Error: Failed to allocate memory!"));
		cub->map[0].row = line;
		cub->map[0].columns = ft_strlen(line);
		cub->rows_nb = 1;
		return (SUCCESS);
	}
	i = -1;
	tmap = cub->map;
	if(!(cub->map = malloc(++(cub->rows_nb) * sizeof(t_map))))
		return (exit_error(cub, "Error: Failed to allocate memory!"));
	while (++i < cub->rows_nb - 1)
		cub->map[i] = tmap[i];
	cub->map[i].row = line;
	cub->map[i].columns = ft_strlen(line);
	free(tmap);
	return (SUCCESS);
}

int		set_camera_rotation(t_cub *cub, char direction)
{
	if (direction == 'N')
		cub->cam.ang = RAD(270);
	else if (direction == 'W')
		cub->cam.ang = RAD(180);
	else if (direction == 'S')
		cub->cam.ang = RAD(90);
	else if (direction == 'E')
		cub->cam.ang = RAD(0);
	return (SUCCESS);
}

t_bool	is_camera(t_cub *cub, int i, int j)
{
	if (value_at(cub, i, j) == 'N' || value_at(cub, i, j) == 'W' ||
		value_at(cub, i, j) == 'S' || value_at(cub, i, j) == 'E')
		return (TRUE);
	return (FALSE);
}

int		init_camera(t_cub *cub)
{
	t_bool		cam_exists;
	int			i;
	int			j;

	j = -1;
	cam_exists = FALSE;
	while (++j < cub->rows_nb)
	{
		i = -1;
		while (++i < cub->map[j].columns)
		{
			if (is_camera(cub, i, j))
			{
				if (cam_exists)
					return (exit_error(cub, "Error: Only one Player is required!"));
				cam_exists = TRUE;
				set_camera_rotation(cub, value_at(cub, i, j));
				cub->cam.x = (i + 0.5F) * TILE_SIZE;
				cub->cam.y = (j + 0.5F) * TILE_SIZE;
			}
		}
	}
	return (!cam_exists ? 
			exit_error(cub, "Error: Player doesn't exist in Map!") : SUCCESS);
}

int		handle_line(t_cub *cub, t_str line)
{
	if (IS_SUCESS(ft_strncmp(line, "R ", 2)))
		return (read_resolution(cub, line));
	else if (IS_SUCESS(ft_strncmp(line, "NO", 2)))
		return (read_xpm(cub, line, NORTH));
	else if (IS_SUCESS(ft_strncmp(line, "SO", 2)))
		return (read_xpm(cub, line, SOUTH));
	else if (IS_SUCESS(ft_strncmp(line, "WE", 2)))
		return (read_xpm(cub, line, WEST));
	else if (IS_SUCESS(ft_strncmp(line, "EA", 2)))
		return (read_xpm(cub, line, EAST));
	else if (IS_SUCESS(ft_strncmp(line, "S ", 2)))
		return (read_xpm(cub, line, SPR));
	else if (IS_SUCESS(ft_strncmp(line, "F ", 2)))
		return (read_color(cub, line, FLOOR));
	else if (IS_SUCESS(ft_strncmp(line, "C ", 2)))
		return (read_color(cub, line, CIEL));
	else if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
		return (read_map(cub, line));
	else if (line[0] != '\0')
		return (exit_error(cub, "Error: File malformed!, Unrecognized characters!"));
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
	if (IS_ERROR(check_map(cub)))
		return (ERROR);
	if (IS_ERROR(init_camera(cub)))
		return (ERROR);
	return (SUCCESS);
}