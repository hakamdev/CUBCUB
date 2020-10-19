#include "../include/cubengine.h"
#include "../include/get_next_line.h"

int		free_2d(t_str *str)
{
	int		i;

	i = 0;
	while (str[i] != NULL)
		free(str[i++]);
	free(str);
	return (SUCCESS);
}

int		read_resolution(t_cub *cub, t_str line)
{
	t_str	*split;

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

int		init_read(t_cub *cub)
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