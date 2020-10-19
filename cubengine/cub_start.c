/* ***
NAMING CONVENTIONS
	init { reset } -> render/draw
*** */

#include "../include/cubengine.h"

int		exit_error( t_cub *cub, t_str error_msg)
{
	if (error_msg)
		cub->errno = error_msg;
	return (ERROR);
}

int		check_filename(t_str filename)
{
	int		len;

	len = ft_strlen(filename);
	if (IS_SUCESS(ft_strncmp(&filename[len - 3], ".cub", 6)))
		return (SUCCESS);
	return (ERROR);
}

int		init_args( t_cub *cub, int argc, const t_str *args)
{
	if (argc < 2)
		return (exit_error(&cub, "Error: At least 1 arg is required!"));
	if (argc > 3)
		return(exit_error(cub, "Error: Too many arguments!"));
	if (IS_ERROR(check_filename(args[1])))
		return(exit_error(cub, "Error: File is not supported, provide .cub file!"));
	if (argc == 3 && IS_SUCESS(ft_strncmp(args[2], "--save", 6)))
		cub->screenshot = TRUE;
	else
		return(exit_error(cub, "Error: 2nd arg is not recognized! provide --save instead for screenshot!"));
}

int		main(int argc, char **argv)
{
	t_cub	cub;
	init_args(&cub, argc, argv);
}