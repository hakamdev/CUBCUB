#include "../include/cubengine.h"

int		main(int argc, char **argv)
{
	t_cub	cub;

	if (IS_ERROR(init_game(&cub, argc, argv)))
		return (clean(&cub, ERROR));
	if (cub.screenshot)
	{
		if (IS_ERROR(take_screenshot(&cub)))
			return (clean(&cub, ERROR));
		return (clean(&cub, SUCCESS));
	}
	mlx_hook(cub.window, EV_KEY_PRESSED, 1L << 0, event_key_pressed, &cub);
	mlx_hook(cub.window, EV_KEY_RELEASED, 1L << 1, event_key_released, &cub);
	mlx_loop_hook(cub.mlx, event_game_loop, &cub);
	mlx_loop(cub.mlx);
	return (SUCCESS);
}
