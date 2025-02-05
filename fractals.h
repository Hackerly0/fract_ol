/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:25:36 by hnisirat          #+#    #+#             */
/*   Updated: 2025/02/05 13:25:37 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
