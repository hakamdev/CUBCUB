#include "../include/cubengine.h"

int		init_textures_extra(t_cub *cub)
{
	if (!(cub->txt[SPR].img = mlx_xpm_file_to_image(cub->mlx,
	cub->txt[SPR].path, &cub->txt[SPR].width, &cub->txt[SPR].height)))
		return (exit_error(cub, "Error: XPM file is not valid or doesn't exist!"));
	if (!(cub->txt[HUD].img = mlx_xpm_file_to_image(cub->mlx,
	cub->txt[HUD].path, &cub->txt[HUD].width, &cub->txt[HUD].height)))
		return (exit_error(cub, "Error: XPM file is not valid or doesn't exist!"));
	cub->txt[SPR].data = (int *)mlx_get_data_addr(cub->txt[SPR].img,
		&cub->txt[SPR].bpp, &cub->txt[SPR].sl, &cub->txt[SPR].end);
	cub->txt[HUD].data = (int *)mlx_get_data_addr(cub->txt[HUD].img,
		&cub->txt[HUD].bpp, &cub->txt[HUD].sl, &cub->txt[HUD].end);
	cub->txt[HUD].vratio = (float)cub->txt[HUD].height / WIN_HEIGHT;
	cub->txt[HUD].hratio = (float)cub->txt[HUD].width / WIN_WIDTH;
	return (SUCCESS);
}

int		init_textures(t_cub *cub)
{
	if (!(cub->txt[NORTH].img = mlx_xpm_file_to_image(cub->mlx,
	cub->txt[NORTH].path, &cub->txt[NORTH].width, &cub->txt[NORTH].height)))
		return (exit_error(cub, "Error: XPM file is not valid or doesn't exist!"));
	if (!(cub->txt[SOUTH].img = mlx_xpm_file_to_image(cub->mlx,
	cub->txt[SOUTH].path, &cub->txt[SOUTH].width, &cub->txt[SOUTH].height)))
		return (exit_error(cub, "Error: XPM file is not valid or doesn't exist!"));
	if (!(cub->txt[WEST].img = mlx_xpm_file_to_image(cub->mlx,
	cub->txt[WEST].path, &cub->txt[WEST].width, &cub->txt[WEST].height)))
		return (exit_error(cub, "Error: XPM file is not valid or doesn't exist!"));
	if (!(cub->txt[EAST].img = mlx_xpm_file_to_image(cub->mlx,
	cub->txt[EAST].path, &cub->txt[EAST].width, &cub->txt[EAST].height)))
		return (exit_error(cub, "Error: XPM file is not valid or doesn't exist!"));
	cub->txt[NORTH].data = (int *)mlx_get_data_addr(cub->txt[NORTH].img,
		&cub->txt[NORTH].bpp, &cub->txt[NORTH].sl, &cub->txt[NORTH].end);
	cub->txt[SOUTH].data = (int *)mlx_get_data_addr(cub->txt[SOUTH].img,
		&cub->txt[SOUTH].bpp, &cub->txt[SOUTH].sl, &cub->txt[SOUTH].end);
	cub->txt[WEST].data = (int *)mlx_get_data_addr(cub->txt[WEST].img,
		&cub->txt[WEST].bpp, &cub->txt[WEST].sl, &cub->txt[WEST].end);
	cub->txt[EAST].data = (int *)mlx_get_data_addr(cub->txt[EAST].img,
		&cub->txt[EAST].bpp, &cub->txt[EAST].sl, &cub->txt[EAST].end);
	return (init_textures_extra(cub));
}

int		init_sprites(t_cub *cub)
{
	int		i;
	int		j;

	j = -1;
	while (++j < cub->rows_nb)
	{
		i = -1;
		while (++i < cub->map[j].columns)
			if (ft_strnchar("234", value_at(cub, i, j)))
			{
				if (IS_ERROR(add_sprite(cub, i, j)))
					return (exit_error(cub, "Error: Failed to allocate memory!"));
			}
	}
	return (SUCCESS);
}

int		init_rays(t_cub *cub)
{
	int		i;

	i = -1;
	if (!(cub->ray = malloc(sizeof(t_ray) * WIN_WIDTH)))
		return (exit_error(cub, "Error: Failed to allocate memory!"));
	while (++i < WIN_WIDTH)
	{
		cub->ray[i].dist = 0.0F;
		cub->ray[i].hit[X] = 0.0F;
		cub->ray[i].hit[Y] = 0.0F;
		cub->ray[i].hitver = FALSE;
		init_ray(&cub->ray[i]);
	}
	return (SUCCESS);
}

