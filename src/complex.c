#include "fractol.h"

t_complex	*init_complex(long double re, long double im)
{
	t_complex *z = (t_complex *) malloc(sizeof(t_complex));
	if (!z)
		return (0);
	z->re = re;
	z->im = im;
	return (z);
}

t_complex	*set_complex(t_complex *z, long double re, long double im)
{
	if (!z)
		return (z);
	z->re = re;
	z->im = im;
	return (z);
}

// t_complex	*polar_to_dekart(t_complex *z, long double r, long double fi)
// {
// 	set_complex(z, r * cos(fi), r * sin(fi));
// 	return (z);
// }

// t_complex	*dekart_to_polar(t_complex *z, long double x, long double y)
// {
// 	set_complex(z, sqrtl(x * x + y * y), atan2(y, x));
// 	return (z);
// }