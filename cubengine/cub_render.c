#include "../include/cubengine.h"

void	draw(t_img *canvas, int x, int y, int color)
{
    canvas->data[y * canvas->width + x] = color;
}

void    render_hud(t_cub *cub)
{

}

void    render_wall_stripe(t_cub cub, int top, int bttm, int i)
{
    while (top < bttm)
    {
        if (!cub.ray[i].hitver && cub.ray[i].dir[NORTH])
            
    }
    
}
