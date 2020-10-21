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

int		check_filename(t_str filename, int ext)
{
	int		len;

	len = ft_strlen(filename);
	if (IS_SUCESS(ft_strncmp(&filename[len - 4], 
					ext == EXT_CUB ? ".cub" : ".xpm", 6)))
		return (SUCCESS);
	return (ERROR);
}

//
int		init_args( t_cub *cub, int argc, const t_str *args)
{
	if (argc < 2)
		return (exit_error(cub, "Error: At least 1 argument is required!"));
	if (argc > 3)
		return(exit_error(cub, "Error: Too many arguments!"));
	if (IS_ERROR(check_filename(args[1], EXT_CUB)))
		return(exit_error(cub, "Error: File is not supported, provide .cub file!"));
	cub->fname = args[1];
	if (argc == 3 && IS_SUCESS(ft_strncmp(args[2], "--save", 6)))
		cub->screenshot = TRUE;
	else if (argc == 3)
		return(exit_error(cub, "Error: 2nd arg is not recognized! provide --save instead for screenshot!"));
	return (SUCCESS);
}

int		init_cub(t_cub *cub)
{
	int		i;

	i =						-1;
	cub->cam.x =			-1;
	cub->cam.y =			-1;
	cub->read_nb = 			0;
	cub->cnvs.width = 		0;
	cub->cnvs.height = 		0;
	cub->errno =			NULL;
	cub->fname =			NULL;
	cub->screenshot = 		FALSE;
	cub->map = 				NULL;
	cub->cam.mov_dir =		FALSE;
	cub->cam.rot_dir =		FALSE;
	while (++i < 6)
		cub->txt[i].path =	NULL;
	return (SUCCESS);
}

int		main(int argc, char **argv)
{
	t_cub	cub;

	init_cub(&cub);
	if (IS_ERROR(init_args(&cub, argc, argv)))
		return (ft_output(cub.errno, ERROR));
	if (IS_ERROR(ft_init_read(&cub)))
		return (ft_output(cub.errno, ERROR));
	
	/* TEST */
	printf("R [%i, %i]\n", cub.cnvs.width, cub.cnvs.height);
	printf("C [%i, %i, %i]\n", cub.color[CIEL].r, cub.color[CIEL].g, cub.color[CIEL].b);
	printf("F [%i, %i, %i]\n", cub.color[FLOOR].r, cub.color[FLOOR].g, cub.color[FLOOR].b);
	printf("NO [%s]\n", cub.txt[NORTH].path);
	printf("SO [%s]\n", cub.txt[SOUTH].path);
	printf("WE [%s]\n", cub.txt[WEST].path);
	printf("EA [%s]\n", cub.txt[EAST].path);
	printf("S [%s]\n", cub.txt[SPR].path);

	printf("cam: x[%i], y[%i], ang[%f]\n", cub.cam.x, cub.cam.y, DEG(cub.cam.ang));
	/* END TEST */
}
