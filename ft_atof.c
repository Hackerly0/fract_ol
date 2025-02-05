/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:25:56 by hnisirat          #+#    #+#             */
/*   Updated: 2025/02/05 13:25:58 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

static bool	is_valid_input(const char *str)
{
	int		i;
	int		dot_count;

	if (!str || !str[0])
		return (false);
	i = 0;
	dot_count = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else if (str[i] == '.' && dot_count == 0)
		{
			dot_count++;
			i++;
		}
		else
			return (false);
	}
	return (true);
}

static void	process_integer_part(const char *str, int *i, double *number)
{
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		*number = *number * 10 + (str[*i] - '0');
		(*i)++;
	}
}

static void	process_fractional_part(const char *str, int *i, double *number)
{
	double	fraction;

	fraction = 0.1;
	(*i)++;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		*number += (str[*i] - '0') * fraction;
		fraction *= 0.1;
		(*i)++;
	}
}

static double	read_number(const char *str, int *i)
{
	int		sign;
	double	number;

	sign = 1;
	number = 0;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	process_integer_part(str, i, &number);
	if (str[*i] == '.')
		process_fractional_part(str, i, &number);
	return (number * sign);
}

double	ft_atof(const char *str)
{
	int	i;

	if (str == NULL)
		return (0.0);
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (!is_valid_input(str + i))
		return (0.0);
	return (read_number(str, &i));
}
