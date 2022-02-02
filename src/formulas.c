#include "fractol.h"

void	_2_z(t_complex *z) // 2z
{
	z->re *= 2;
	z->im *= 2;
}

void	z_2_p_c(t_complex *z, t_complex *c) // z^2 + c
{
	long double	tmp_re;

	tmp_re = z->re;
	z->re = z->re * z->re - z->im * z->im + c->re;
	z->im = 2 * tmp_re * z->im + c->im;
}

void	abs_z_2_p_c(t_complex *z, t_complex *c) // |z|^2 + c
{
	long double	tmp_re;

	tmp_re = z->re;
	z->re = z->re * z->re - z->im * z->im + c->re;
	z->im = 2 * ABS(tmp_re) * ABS(z->im) + c->im;
}

void	z_3_p_c(t_complex *z, t_complex *c) // z^3 + c
{
	long double	tmp_re;

	tmp_re = z->re;
	z->re = (z->re * z->re * z->re) - 3 * (z->re * z->im * z->im) + c->re;
	z->im = 3 * (tmp_re * tmp_re * z->im) - (z->im * z->im * z->im) + c->im;
}

void	z_4_p_c(t_complex *z, t_complex *c) // z^4 + c
{
	long double	tmp_re;

	tmp_re = z->re;
	z->re = (z->re * z->re * z->re * z->re) - 6 * (z->re * z->re * z->im * z->im) + (z->im * z->im * z->im * z->im) + c->re;
	z->im = 4 * tmp_re * z->im * (tmp_re * tmp_re - z->im * z->im) + c->im;
}

void	_3_z_2(t_complex *z) // 3z^2
{
	long double	tmp_re;

	tmp_re = z->re;
	z->re = 3 * (z->re * z->re - z->im * z->im);
	z->im = 6 * tmp_re * z->im;
}

void	_4_z_3(t_complex *z) // 4z^3
{
	long double	tmp_re;

	tmp_re = z->re;
	z->re = 4 * (z->re * z->re * z->re) - 12 * (z->re * z->im * z->im);
	z->im = 12 * (tmp_re * tmp_re * z->im) - 4 * (z->im * z->im * z->im);
}