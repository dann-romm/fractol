/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals_newton.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:07:46 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/05 17:55:33 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	newton_iteraion(t_complex *z)
{
	static t_complex	c;
	static t_complex	f_z;
	static t_complex	fp_z;
	static t_complex	dev;

	if (c.re != -1)
	{
		set_complex(&c, -1, 0);
		set_complex(&f_z, z->re, z->im);
		set_complex(&fp_z, z->re, z->im);
		set_complex(&dev, 0, 0);
	}
	else
	{
		set_complex(&f_z, z->re, z->im);
		set_complex(&fp_z, z->re, z->im);
	}
	z_4_p_c(&f_z, &c);
	_4_z_3(&fp_z);
	set_complex(&dev, (f_z.re * fp_z.re + f_z.im * fp_z.im) / (fp_z.re
			* fp_z.re + fp_z.im * fp_z.im), (fp_z.re * f_z.im - fp_z.im
			* f_z.re) / (fp_z.re * fp_z.re + fp_z.im * fp_z.im));
	z->re = z->re - dev.re;
	z->im = z->im - dev.im;
}

int	newton(t_mlx_data *data, t_complex *z)
{
	const int		max_iterations = 32;
	int				iterations;
	t_complex		*z1;

	z1 = data->point;
	set_complex(z1, 0, 0);
	iterations = -1;
	while (++iterations < max_iterations)
	{
		z1 = set_complex(z1, z->re, z->im);
		newton_iteraion(z);
	}
	if (z->re > z->im)
	{
		if (z->re > -z->im)
			return (0x00FFFF);
		return (0xFFFF00);
	}
	else
	{
		if (z->re > -z->im)
			return (0xFF00FF);
		return (0x7F7FFF);
	}
}
