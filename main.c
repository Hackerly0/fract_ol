/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:26:43 by hnisirat          #+#    #+#             */
/*   Updated: 2025/02/05 13:26:45 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"
#include <stdlib.h>

static double	check_input(const char *str)
{
	double	i;
	size_t	j;
	int		dot_count;

	dot_count = 0;
	if (!str || str[0] == '\0')
		exit(1);
	i = ft_atof(str);
	if (i > 2 || i < -2)
		exit(1);
	j = 0;
	while (str[j] != '\0')
	{
		if (str[j] == '.')
			dot_count++;
		if (!((str[j] >= '0' && str[j] <= '9') || str[j] == '.'
				|| (j == 0 && (str[j] == '-' || str[j] == '+'))))
			exit(1);
		j++;
	}
	if (dot_count > 1)
		exit(1);
	return (i);
}

void	init_vars(t_vars *vars)
{
	vars->zoom = 1.0;
	vars->offset_x = 0.0;
	vars->offset_y = 0.0;
}

void	setup_hooks(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_mouse_hook(vars->win, handle_mouse, vars);
	mlx_hook(vars->win, 2, 1L << 0, handle_keypress, vars);
	mlx_hook(vars->win, 17, 0, close_window, vars);
}

int	check_vars(int argc, char **argv)
{
	return ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 11)) || (argc == 4
			&& !ft_strncmp(argv[1], "julia", 6)));
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (check_vars(argc, argv))
	{
		if (!ft_strncmp(argv[1], "mandelbrot", 10))
			vars.fractal = 1;
		else if (!ft_strncmp(argv[1], "julia", 5))
		{
			vars.juila_re = check_input(argv[2]);
			vars.julia_img = check_input(argv[3]);
			vars.fractal = 2;
		}
		ft_init_graphics(&vars);
		init_vars(&vars);
		draw_fractal(&vars);
		setup_hooks(&vars);
		mlx_loop(vars.mlx);
	}
	else
	{
		errno = EINVAL;
		perror("Usage: ./fract_ol mandelbrot-julia <real> <imaginary>");
		exit(1);
	}
	return (0);
}
