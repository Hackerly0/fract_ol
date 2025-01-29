int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

unsigned char	get_t(int trgb)
{
	return (((unsigned char *)&trgb)[3]);
}

unsigned char	get_r(int trgb)
{
	return (((unsigned char *)&trgb)[2]);
}

unsigned char	get_g(int trgb)
{
	return (((unsigned char *)&trgb)[1]);
}

unsigned char	get_b(int trgb)
{
	return (((unsigned char *)&trgb)[0]);
}

/* since a single color is a 8 bits integer (0 - 255), we can represent colors in an int (4 bytes).
A color can perfectly fit in an an unsigned char, so we can create an array of unsigned chars,
and it can be used as an array of 4 bytes (transparent, red, green, blue).
Using type-casting, we can retrive the color in an integer format.
To get each single color value, we use bitwise operators.*/