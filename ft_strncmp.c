/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnisirat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:20:20 by hnisirat          #+#    #+#             */
/*   Updated: 2024/08/29 14:38:57 by hnisirat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	u1;
	unsigned char	u2;

	i = 0;
	while (i < n)
	{
		u1 = (unsigned char)s1[i];
		u2 = (unsigned char)s2[i];
		if (u1 != u2)
			return (u1 - u2);
		if (u1 == '\0')
			return (0);
		i++;
	}
	return (0);
}

/*int	main(void)
{
	char	s[] = "this is my ";
	char	c[] = "th222s js my ";
	int i = ft_strncmp(s, c, 7);
	printf("%d", i);
	return (0);
}*/
