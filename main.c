#include "fract_ol.h"

int main(int argc, char *argv[])
{
	t_vars *vars;

	vars = malloc(sizeof(t_vars));
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Mandelbrot Set");
	vars->img.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
									&vars->img.line_length, &vars->img.endian);
	vars->zoom = 1.0;
	vars->offset_x = 0.0;
	vars->offset_y = 0.0;
	mlx_mouse_hook(vars->win, handle_mouse, vars);
	draw_julia(&vars->img, vars, -0.8, 0.156);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_hook(vars->win, 2, 1L << 0, handle_keypress, vars);
	mlx_hook(vars->win, 17, 0, close_window, vars);
	mlx_loop(vars->mlx);

	return (0);
}