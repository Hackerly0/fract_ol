#include "fract_ol.h"

typedef struct s_mouse
{
	double	zoom_factor;
	double	real_range;
	double	img_range;
	double	mouse_real;
	double	mouse_img;
}	t_mouse;

void	intialize_mouse(t_mouse *list)
{
	list->img_range = 0;
	list->mouse_img = 0;
	list->mouse_real = 0;
	list->real_range = 0;
	list->zoom_factor = 0;
}

int	handle_mouse(int button, int x, int y, void *param)
{
	t_vars	*vars;
	t_mouse	list;

	vars = (t_vars *)param;
	intialize_mouse(&list);
	if (button == 4)
		list.zoom_factor = 0.8;
	else
		list.zoom_factor = 1.2;
	list.real_range = (MAX_REAL - MIN_REAL) / vars->zoom;
	list.img_range = (MAX_IMG - MIN_IMG) / vars->zoom;
	list.mouse_real = MIN_REAL + (x / (double)WIDTH)
		* list.real_range + vars->offset_x * list.real_range;
	list.mouse_img = MIN_IMG + (y / (double)HEIGHT)
		* list.img_range + vars->offset_y * list.img_range;
	vars->zoom *= list.zoom_factor;
	list.real_range = (MAX_REAL - MIN_REAL) / vars->zoom;
	list.img_range = (MAX_IMG - MIN_IMG) / vars->zoom;
	vars->offset_x = (list.mouse_real - MIN_REAL) / list.real_range
		- (x / (double)WIDTH);
	vars->offset_y = (list.mouse_img - MIN_IMG) / list.img_range
		- (y / (double)HEIGHT);
	draw_julia(&vars->img, vars, -0.8, 0.156);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

int	handle_keypress(int keycode, void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	if (keycode == 65307)
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(0);
	}
	return (0);
}

int	close_window(void *param)
{
	t_vars	*vars;

	vars = (t_vars *)param;
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}
