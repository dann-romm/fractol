/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formulas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:48:40 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/05 16:55:54 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// z^2 + c
void	z_2_p_c(t_complex *z, t_complex *c)
{
	long double	tmp_re;

	tmp_re = z->re;
	z->re = z->re * z->re - z->im * z->im + c->re;
	z->im = 2 * tmp_re * z->im + c->im;
}

// |z|^2 + c
void	abs_z_2_p_c(t_complex *z, t_complex *c)
{
	long double	tmp_re;

	tmp_re = z->re;
	z->re = z->re * z->re - z->im * z->im + c->re;
	z->im = 2 * abs_double(tmp_re) * abs_double(z->im) + c->im;
}

// z^3 + c
void	z_3_p_c(t_complex *z, t_complex *c)
{
	long double	tmp_re;

	tmp_re = z->re;
	z->re = (z->re * z->re * z->re) - 3 * (z->re * z->im * z->im) + c->re;
	z->im = 3 * (tmp_re * tmp_re * z->im) - (z->im * z->im * z->im) + c->im;
}

// z^4 + c
void	z_4_p_c(t_complex *z, t_complex *c)
{
	long double	tmp_re;

	tmp_re = z->re;
	z->re = (z->re * z->re * z->re * z->re) - 6 * (z->re * z->re
			* z->im * z->im) + (z->im * z->im * z->im * z->im) + c->re;
	z->im = 4 * tmp_re * z->im * (tmp_re * tmp_re - z->im * z->im) + c->im;
}

// 4z^3
void	_4_z_3(t_complex *z)
{
	long double	tmp_re;

	tmp_re = z->re;
	z->re = 4 * (z->re * z->re * z->re) - 12 * (z->re * z->im * z->im);
	z->im = 12 * (tmp_re * tmp_re * z->im) - 4 * (z->im * z->im * z->im);
}
