/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:08:53 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/05 16:10:20 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_in(t_mlx_data *data, int x, int y)
{
	data->scale *= 1.6;
	data->shift_x -= x;
	data->shift_x /= 1.6;
	data->shift_x += x;
	data->shift_y -= y;
	data->shift_y /= 1.6;
	data->shift_y += y;
}

void	zoom_out(t_mlx_data *data, int x, int y)
{
	data->scale *= 0.625;
	data->shift_x -= x;
	data->shift_x /= 0.625;
	data->shift_x += x;
	data->shift_y -= y;
	data->shift_y /= 0.625;
	data->shift_y += y;
}

void	right_shift(t_mlx_data *data, int dx, int dy)
{
	int	color;
	int	x;
	int	y;

	y = HEIGHT;
	while (--y > dy - 1)
	{
		x = WIDTH;
		while (--x > dx - 1)
			ft_mlx_pixel_put(data->img, x, y,
				get_color(data->img, x - dx, y - dy));
	}
	data->shift_x += dx;
	data->shift_y += dy;
	data->x_bound = dx;
	data->y_bound = dy;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}

void	left_shift(t_mlx_data *data, int dx, int dy)
{
	int	color;
	int	x;
	int	y;

	y = dy - 1;
	while (++y < HEIGHT)
	{
		x = dx - 1;
		while (++x < WIDTH)
			ft_mlx_pixel_put(data->img, x - dx, y - dy,
				get_color(data->img, x, y));
	}
	data->shift_x -= dx;
	data->shift_y -= dy;
	data->x_bound = -dx;
	data->y_bound = -dy;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}
