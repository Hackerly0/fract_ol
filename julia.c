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

static void	init_vars(t_list *data, double *z_re, double *z_im)
{

	data->c_im = 0;
	data->c_re = 0;
	data->color = 0;
	data->iter = 0;
	data->pixel = NULL;
	data->x = 0;
	data->y = 0;
	z_re = 0;
	z_im = 0;
}

static int	get_color(int iter, int max_iter)
{
	if (iter == max_iter)
		return (0x000000);
	return ((int)(0xFFFFFF * ((double)iter / max_iter)));
}

int	julia(double z_re, double z_im, double c_re, double c_im)
{
	int		iter;
	double	tmp;

	iter = 0;
	tmp = 0;
	while (z_re * z_re + z_im * z_im <= 4 && iter < MAX_ITER)
	{
		tmp = z_re * z_re - z_im * z_im + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = tmp;
		iter++;
	}
	return (iter);
}

void	draw_julia(t_data *img, double c_re_julia, double c_im_julia)
{
	t_list	list;
	double	z_re;
	double	z_im;

	init_vars(&list, &z_re, &z_im);
	while (list.y < HEIGHT)
	{
		list.x = 0;
		while (list.x < WIDTH)
		{
			z_re = MIN_REAL + (double)list.x / WIDTH
				* (MAX_REAL - MIN_REAL);
			z_im = MIN_IMG + (double)list.y / HEIGHT
				* (MAX_IMG - MIN_IMG);
			list.iter = julia(z_re, z_im, c_re_julia, c_im_julia);
			list.color = get_color(list.iter, MAX_ITER);
			list.pixel = img->addr + (list.y * img->line_length + list.x
					* (img->bits_per_pixel / 8));
			*(unsigned int *)list.pixel = list.color;
			list.x++;
		}
		list.y++;
	}
}
