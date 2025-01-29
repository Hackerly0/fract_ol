#include "fract_ol.h"

typedef struct s_list
{
	int		y;
	int		x;
	int		iter;
	int		color;
	double	c_im;
	double	c_re;
	char	*pixel;
}	t_list;

static void	init_vars(t_list *data)
{
	data->c_im = 0;
	data->c_re = 0;
	data->color = 0;
	data->iter = 0;
	data->pixel = NULL;
	data->x = 0;
	data->y = 0;
}

static int	get_color(int iter, int max_iter)
{
	if (iter == max_iter)
		return (0x000000);
	return ((int)(0xFFFFFF * ((double)iter / max_iter)));
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

void    draw_mandelbrot(t_data *img, t_vars *vars) { // Add t_vars* parameter
    t_list  list;
    init_vars(&list);

    // Calculate adjusted bounds using zoom and offset
    double real_range = (MAX_REAL - MIN_REAL) / vars->zoom;
    double img_range = (MAX_IMG - MIN_IMG) / vars->zoom;
    double adj_min_real = MIN_REAL + real_range * vars->offset_x;
    double adj_min_img = MIN_IMG + img_range * vars->offset_y;

    list.y = 0;
    while (list.y < HEIGHT) {
        list.x = 0;
        while (list.x < WIDTH) {
            // Apply zoom and offset to coordinates
            list.c_re = adj_min_real + (double)list.x / WIDTH * real_range;
            list.c_im = adj_min_img + (double)list.y / HEIGHT * img_range;

            list.iter = mandelbrot(list.c_re, list.c_im);
            list.color = get_color(list.iter, MAX_ITER);
            list.pixel = img->addr + (list.y * img->line_length + list.x * (img->bits_per_pixel / 8));
            *(unsigned int *)list.pixel = list.color;
            list.x++;
        }
        list.y++;
    }
}