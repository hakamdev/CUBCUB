#include "../include/cubengine.h"

void	draw(t_img *canvas, int x, int y, int color)
{
    canvas->data[y * canvas->width + x] = color;
}