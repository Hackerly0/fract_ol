/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:26:25 by hnisirat          #+#    #+#             */
/*   Updated: 2025/02/05 13:26:27 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	ft_error_exit(char *message)
{
	perror(message);
	exit(1);
}

void	ft_free_graphics(t_vars *graphics)
{
	if (!graphics)
		return ;
	if (graphics->img.img)
	{
		mlx_destroy_image(graphics->mlx, graphics->img.img);
		graphics->img.img = NULL;
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

void	ft_init_graphics(t_vars *gfx)
{
	gfx->mlx = mlx_init();
	if (!gfx->mlx)
		ft_error_exit("Failed to initialize MLX");
	gfx->win = mlx_new_window(gfx->mlx, WIDTH, HEIGHT, "Fract-ol");
	if (!gfx->win)
	{
		ft_free_graphics(gfx);
		ft_error_exit("Failed to create MLX window");
	}
	gfx->img.img = mlx_new_image(gfx->mlx, WIDTH, HEIGHT);
	if (!gfx->img.img)
	{
		ft_free_graphics(gfx);
		ft_error_exit("Failed to create MLX image");
	}
	gfx->img.addr = mlx_get_data_addr(gfx->img.img, &gfx->img.bpp,
			&gfx->img.line_len, &gfx->img.endian);
	if (!gfx->img.addr)
	{
		ft_free_graphics(gfx);
		ft_error_exit("Failed to get image data address");
	}
}
