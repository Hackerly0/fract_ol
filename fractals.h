#ifndef FRACTALS_H
# define FRACTALS_H

typedef struct s_list
{
	int		y;
	int		x;
	int		iter;
	int		color;
	double	c_im;
	double	c_re;
	char	*pixel;
	double	z_re;
	double	z_im;
	double	real_range;
	double	img_range;
	double	adj_min_real;
	double	adj_min_img;
}	t_list;
#endif