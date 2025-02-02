double	ft_atof(const char *str)
{
	int		i;
	int		sign;
	double	number;
	double	fraction;

	i = 0;
	sign = 1;
	number = 0;
	fraction = 1;
	if (str[0] == '\0')
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			fraction /= 10;
			number += (str[i] - '0') * fraction;
			i++;
		}
	}
	return (number * sign);
}