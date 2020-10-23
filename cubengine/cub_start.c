#include "../include/cubengine.h"


int		handle_args( t_cub *cub, int argc, const t_str *args)
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

int		clean(t_cub *cub, int retcode)
{

	return (retcode);
}

int		main(int argc, char **argv)
{
	t_cub	cub;

	if (IS_ERROR(init_game(&cub, argc, argv)))
		return (clean(&cub, ERROR));
	mlx_hook(cub.window, EV_KEY_PRESSED, 1L << 0, key_pressed, &cub);
	mlx_hook(cub.window, EV_KEY_RELEASED, 1L << 1, key_released, &cub);
	mlx_loop_hook(cub.mlx, cub_game_loop, &cub);
	return (SUCCESS);
	/* TEST */
	// printf("R [%i, %i]\n", cub.cnvs.width, cub.cnvs.height);
	// printf("C [%i, %i, %i]\n", cub.color[CIEL].r, cub.color[CIEL].g, cub.color[CIEL].b);
	// printf("F [%i, %i, %i]\n", cub.color[FLOOR].r, cub.color[FLOOR].g, cub.color[FLOOR].b);
	// printf("NO [%s]\n", cub.txt[NORTH].path);
	// printf("SO [%s]\n", cub.txt[SOUTH].path);
	// printf("WE [%s]\n", cub.txt[WEST].path);
	// printf("EA [%s]\n", cub.txt[EAST].path);
	// printf("S [%s]\n", cub.txt[SPR].path);

	// printf("cam: x[%i], y[%i], ang[%f]\n", cub.cam.x, cub.cam.y, DEG(cub.cam.ang));
	/* END TEST */
}
