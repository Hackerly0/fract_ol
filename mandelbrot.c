#include "fract_ol.h"
#include "fractals.h"

static void	init_vars(t_list *data)
{
	data->c_im = 0;
	data->c_re = 0;
	data->color = 0;
	data->iter = 0;
	data->pixel = NULL;
	data->x = 0;
	data->y = 0;
	data->real_range = 0;
	data->img_range = 0;
	data->adj_min_real = 0;
	data->adj_min_img = 0;
}

static int	get_color(int iter, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iter == max_iter)
		return (0x000000);
	t = (double)iter / max_iter;
	r = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(9 * (1 - t) * t * t * t * 255);
	return ((r << 16) | (g << 8) | b);
}

int	mandelbrot(double c_re, double c_im)
{
	double	z_re;
	double	z_im;
	double	tmp;
	int		iter;

	z_re = 0;
	z_im = 0;
	iter = 0;
	while (z_re * z_re + z_im * z_im <= 4 && iter < MAX_ITER)
	{
		tmp = z_re * z_re - z_im * z_im + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = tmp;
		iter++;
	}
	return (iter);
}

void	draw_mandelbrot(t_data *img, t_vars *vars)
{
	t_list	list;

	init_vars(&list);
	list.real_range = (MAX_REAL - MIN_REAL) / vars->zoom;
	list.img_range = (MAX_IMG - MIN_IMG) / vars->zoom;
	list.adj_min_real = MIN_REAL + list.real_range * vars->offset_x;
	list.adj_min_img = MIN_IMG + list.img_range * vars->offset_y;
	while (list.y < HEIGHT)
	{
		list.x = 0;
		while (list.x < WIDTH)
		{
			list.c_re = list.adj_min_real + (double)list.x
				/ WIDTH * list.real_range;
			list.c_im = list.adj_min_img + (double)list.y
				/ HEIGHT * list.img_range;
			list.iter = mandelbrot(list.c_re, list.c_im);
			list.color = get_color(list.iter, MAX_ITER);
			list.pixel = img->addr + (list.y * img->line_len
					+ list.x * (img->bpp / 8));
			*(unsigned int *)list.pixel = list.color;
			list.x++;
		}
		list.y++;
	}
}
// void	draw_mandelbrot(t_data *img)
// {
// 	t_list	list;

// 	init_vars(&list);
// 	while (list.y < HEIGHT)
// 	{
// 		list.x = 0;
// 		while (list.x < WIDTH)
// 		{
// 			list.c_re = MIN_REAL + (double)list.x
// 				/ WIDTH * (MAX_REAL - MIN_REAL);
// 			list.c_im = MIN_IMG + (double)list.y
// 				/ HEIGHT * (MAX_IMG - MIN_IMG);
// 			list.iter = mandelbrot(list.c_re, list.c_im);
// 			list.color = get_color(list.iter, MAX_ITER);
// 			list.pixel = img->addr + (list.y * img->line_length + list.x
// 					* (img->bits_per_pixel / 8));
// 			*(unsigned int *)list.pixel = list.color;
// 			list.x++;
// 		}
// 		list.y++;
// 	}
// }