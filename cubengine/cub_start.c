#include "../include/cubengine.h"

int		update_splash(t_cub *cub)
{
	update_rendering_hud(cub, &cub->txt[SPLSH]);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->cnvs.img, 0, 0);
	return (SUCCESS);
}

int		init_splash_screen(t_cub *cub)
{
	if (!(cub->txt[SPLSH].img = mlx_xpm_file_to_image(cub->mlx, "./cubassets/splash.xpm", &cub->txt[SPLSH].width, &cub->txt[SPLSH].height)))
		return (ft_output(cub->errno, exit_error(cub, "Error: Failed to init splash image!")));
	cub->txt[SPLSH].data = (int *)mlx_get_data_addr(cub->txt[SPLSH].img, &cub->txt[SPLSH].bpp, &cub->txt[SPLSH].sl, &cub->txt[SPLSH].end);
	cub->txt[SPLSH].vratio = (float)cub->txt[SPLSH].height / WIN_HEIGHT;
	cub->txt[SPLSH].hratio = (float)cub->txt[SPLSH].width / WIN_WIDTH;
	return (SUCCESS);
}

int		main(int argc, char **argv)
{
	t_cub	cub;

	g_end_splsh = FALSE;
	if (IS_ERROR(init_game(&cub, argc, argv)))
		return (clean(&cub, ERROR));
	if (cub.screenshot)
	{
		if (IS_ERROR(take_screenshot(&cub)))
			return (clean(&cub, ERROR));
		return (clean(&cub, SUCCESS));
	}
	if (IS_ERROR(init_splash_screen(&cub)))
		return(clean(&cub, ERROR));
	mlx_hook(cub.window, EV_KEY_PRESSED, 1L << 0, event_key_pressed, &cub);
	mlx_hook(cub.window, EV_KEY_RELEASED, 1L << 1, event_key_released, &cub);
	mlx_loop_hook(cub.mlx, event_game_loop, &cub);
	mlx_loop(cub.mlx);
	return (SUCCESS);
}
