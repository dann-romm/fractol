/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:07:19 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/05 16:49:20 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	*init_complex(long double re, long double im)
{
	t_complex	*z;

	z = (t_complex *)malloc(sizeof(t_complex));
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
