#include "fract_ol.h"

int main(int argc, char *argv[])
{
	t_vars vars;

	handle_args(argc, argv);
	ft_init_graphics(&vars);
	vars->zoom = 1.0;
	vars->offset_x = 0.0;
	vars->offset_y = 0.0;
	mlx_mouse_hook(vars->win, handle_mouse, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_hook(vars->win, 2, 1L << 0, handle_keypress, vars);
	mlx_hook(vars->win, 17, 0, close_window, vars);
	mlx_loop(vars->mlx);

	return (0);
}