/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:10:42 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/05 17:45:47 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	*(unsigned int *)(img->addr + (y * img->line_length
				+ x * (img->bits_per_pixel / 8))) = color;
}

int	get_color(t_data *img, int x, int y)
{
	return (*(unsigned int *)(img->addr + (y * img->line_length
			+ x * (img->bits_per_pixel / 8))));
}

int	key_hook(int key, t_mlx_data *data)
{
	if (key == 53)
		exit(0);
	else if (key == 0 || key == 2)
	{
		data->color_mode = (data->color_mode + (key / 2 + !key * 7)) % 8;
		if (data->color_mode == 0)
			data->color_mode = (key / 2 + !key * 7);
	}
	else if (key == 1)
		zoom_in(data, WIDTH / 2, HEIGHT / 2);
	else if (key == 13)
		zoom_out(data, WIDTH / 2, HEIGHT / 2);
	else if (key == 123)
		right_shift(data, SHIFT_LENGTH, 0);
	else if (key == 124)
		left_shift(data, SHIFT_LENGTH, 0);
	else if (key == 125)
		left_shift(data, 0, SHIFT_LENGTH);
	else if (key == 126)
		right_shift(data, 0, SHIFT_LENGTH);
	fill_coord_plane(data);
	return (0);
}

int	mouse_hook(int key, int x, int y, t_mlx_data *data)
{
	if (key == 4)
		zoom_in(data, x, HEIGHT - y);
	else if (key == 5)
		zoom_out(data, x, HEIGHT - y);
	fill_coord_plane(data);
	return (0);
}
