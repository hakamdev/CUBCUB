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
	mlx_hook(cub.window, EV_KEY_PRESSED, 1L << 0, event_key_pressed, &cub);
	mlx_hook(cub.window, EV_KEY_RELEASED, 1L << 1, event_key_released, &cub);
	mlx_loop_hook(cub.mlx, event_game_loop, &cub);
	mlx_loop(cub.mlx);
	return (SUCCESS);
}
