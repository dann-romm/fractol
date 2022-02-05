/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:08:38 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/05 20:01:03 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	color_from_iterations(t_mlx_data *data, int it, int max_iterations)
{
	int	intensity;

	intensity = round(0xFF * sqrt((double)it / max_iterations));
	return ((intensity << 16) * (data->color_mode & 1)
		+ (intensity << 8) * ((data->color_mode & 2) >> 1)
		+ intensity * ((data->color_mode & 4) >> 2));
}

int	mandelbrot(t_mlx_data *data, t_complex *c)
{
	void		(*formula)(t_complex *, t_complex *);
	const int	max_iterations = 512 * (1 + (data->scale < 0.0000001));
	int			iterations;
	t_complex	*z;

	z = data->point;
	set_complex(z, 0, 0);
	formula = choose_formula(data->power);
	iterations = -1;
	while (++iterations < max_iterations)
	{
		if (z->im * z->im + z->re * z->re > 4)
			break ;
		formula(z, c);
	}
	if (iterations == max_iterations)
		return (0x000000);
	return (color_from_iterations(data, iterations, max_iterations));
}

int	julia(t_mlx_data *data, t_complex *z)
{
	void		(*formula)(t_complex *, t_complex *);
	const int	max_iterations = 512;
	int			iterations;
	t_complex	*c;

	c = data->point;
	formula = choose_formula(data->power);
	iterations = -1;
	while (++iterations < max_iterations)
	{
		if (z->im * z->im + z->re * z->re > 4)
			break ;
		formula(z, c);
	}
	if (iterations == max_iterations)
		return (0x000000);
	return (color_from_iterations(data, iterations, max_iterations));
}

int	ship(t_mlx_data *data, t_complex *c)
{
	const int	max_iterations = 512;
	int			iterations;
	t_complex	*z;

	z = data->point;
	set_complex(z, 0, 0);
	iterations = -1;
	while (++iterations < max_iterations)
	{
		if (z->im * z->im + z->re * z->re > 4)
			break ;
		abs_z_2_p_c(z, c);
	}
	if (iterations == max_iterations)
		return (0x000000);
	return (color_from_iterations(data, iterations, max_iterations));
}
