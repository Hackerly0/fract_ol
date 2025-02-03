#include "fract_ol.h"

void	ft_free_graphics(t_data *graphics)
{
	if (graphics->img)
	{
		mlx_destroy_image(graphics->mlx, graphics->img);
		graphics->img = NULL;
	}
	if (graphics->win)
	{
		mlx_destroy_window(graphics->mlx, graphics->win);
		graphics->win = NULL;
	}
	if (graphics->mlx)
	{
		mlx_destroy_display(graphics->mlx);
		free(graphics->mlx);
		graphics->mlx = NULL;
	}
}

void	ft_init_graphics(t_vars *graphics)
{
	graphics->mlx = mlx_init();
	if (!graphics->mlx)
		ft_error_exit("Failed to initialize MLX");

	graphics->win = mlx_new_window(graphics->mlx, WIDTH, HEIGHT, "Fract-ol");
	if (!graphics->win)
	{
		ft_free_graphics(graphics);
		ft_error_exit("Failed to create MLX window");
	}

	graphics->img.img = mlx_new_image(graphics->mlx, WIDTH, HEIGHT);
	if (!graphics->img.img)
	{
		ft_free_graphics(graphics);
		ft_error_exit("Failed to create MLX image");
	}

	graphics->img.addr = mlx_get_data_addr(graphics->img.img,
			&graphics->img.bits_per_pixel, &graphics->img.line_length, &graphics->img.endian);
	if (!graphics->img.addr)
	{
		ft_free_graphics(graphics);
		ft_error_exit("Failed to get image data address");
	}
}
