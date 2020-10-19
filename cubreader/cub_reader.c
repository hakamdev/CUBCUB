#include "../include/cubengine.h"
#include "../include/get_next_line.h"

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
	
}

int		init_read(t_cub *cub)
{
	int		map_fd;
	int		retcode;
	char	*line;

	map_fd = open(cub->fname, O_RDONLY);
	if (IS_ERROR(map_fd))
		return (exit_error(cub, "Error: File doesn't exist!"));
	while (!(retcode = get_next_line(map_fd, &line)) > 0)
	{

	}
	
}