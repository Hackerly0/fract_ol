/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:26:35 by hnisirat          #+#    #+#             */
/*   Updated: 2025/02/05 13:26:36 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	data->z_re = 0;
	data->z_im = 0;
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

void	draw_julia(t_data *img, t_vars *vars, double c_re, double c_im)
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
			list.z_re = list.adj_min_real + (double)list.x / WIDTH
				* list.real_range;
			list.z_im = list.adj_min_img + (double)list.y / HEIGHT
				* list.img_range;
			list.iter = julia(list.z_re, list.z_im, c_re, c_im);
			list.color = get_color(list.iter, MAX_ITER);
			list.pixel = img->addr + (list.y * img->line_len + list.x
					* (img->bpp / 8));
			*(unsigned int *)list.pixel = list.color;
			list.x++;
		}
		list.y++;
	}
}
