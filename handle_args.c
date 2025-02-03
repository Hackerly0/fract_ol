#include "fract_ol.h"

int check_argv(char *argv[])
{
	if (argv[2] > 2 || argv[2] < -2)
		return (1);
	if (argv[3] > 2 || argv[3] < -2)
		return (1);
	if (argv[1] != 'm' || argv[1] != 'M' || argv[1] != 'j' || argv[1] != 'J')
		return (1);
	return (0);
}

void    handle_args(int argc, char *argv[])
{
	if (argc < 2 || !check_argv(argv))
	{
		ft_printf("please enter the args like this: %s %s","\nfor mandelbrot: ./fract_ol (m/M) #FFFFFFFFF"
		, "\nfor julia: ./fractol (j/J) -0.6 1.2 #FFFFFFFFF");
		exit(1);
	}
}