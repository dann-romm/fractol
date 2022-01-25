#include "mlx.h"
#include "fractol.h"

t_complex *init_complex(long double re, long double im)
{
	t_complex *z = (t_complex *) malloc(sizeof(t_complex));
	z->re = re;
	z->im = im;
	return (z);
}

t_complex *set_complex(t_complex *z, long double re, long double im)
{
	if (!z)
		return (z);
	z->re = re;
	z->im = im;
	return (z);
}

t_complex *polar_to_dekart(t_complex *z, long double r, long double fi)
{
	set_complex(z, r * cos(fi), r * sin(fi));
	return (z);
}

t_complex *dekart_to_polar(t_complex *z, long double x, long double y)
{
	set_complex(z, sqrtl(x * x + y * y), atan2(y, x));
	return (z);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


// int	is_prime(int n)
// {
// 	if (n < 6)
// 		return ((n > 1) && (n != 4));
// 	if (!(n % 2) || !(n % 3) || !(n % 5))
// 		return (0);
// 	int i = 6;
// 	while (i * i <= n)
// 	{
// 		if (!(n % (i + 1)))
// 			return (0);
// 		if (!(n % (i + 5)))
// 			return (0);
// 		i += 6;
// 	}
// 	return (1);
// }

// void	fill_with_colors(t_data *data, long double resolution)
// {
// 	int color;
// 	t_complex *z = init_complex(0, 0);

// 	int i = 0;
// 	while (++i < 700 / resolution / resolution)
// 	{
// 		z = polar_to_dekart(z, i * resolution, i);
// 		if (point_inside_window(540 + z->re * resolution, 360 + z->im * resolution, 1080, 720))
// 		{
// 			color = 0xFFFFFFFF;
// 			if (is_prime(i))
// 				color = 0x00FFFFFF;
// 			my_mlx_pixel_put(data, 540 + z->re * resolution, 360 + z->im * resolution, color);
// 		}
// 	}
// }

// void	fill_colors(t_data *data)
// {
// 	static int color = 0x00000000;
// 	int x;
// 	int y;
	
// 	int current_color = color;

// 	y = -1;
// 	while (++y < 720)
// 	{
// 		x = -1;
// 		while (++x < 1080)
// 		{
// 			current_color = color;
// 			current_color += 0x00010000 * (x * 0xFF / 1080);
// 			current_color += 0x00000001 * (y * 0xFF / 720);
// 			my_mlx_pixel_put(data, x, y, current_color);
// 		}
// 	}
// 	color++;
// }

// void	paint_spiral(t_data *data)
// {
// 	t_complex *z = init_complex(0, 0);
// 	t_complex *z2 = init_complex(0, 0);
// 	t_complex *z3 = init_complex(0, 0);
// 	t_complex *z4 = init_complex(0, 0);
// 	long double step = 0;
// 	long double k = 0.2;
// 	while (step < 670)
// 	{
// 		z = polar_to_dekart(z, step, step * k);
// 		z2 = polar_to_dekart(z2, step, step * k / 2);
// 		z3 = polar_to_dekart(z3, step, step * k / 3);
// 		z4 = polar_to_dekart(z4, step, step * k / 4);
// 		if (point_inside_window(540 + z->re, 360 + z->im, 1080, 720))
// 			my_mlx_pixel_put(data, 540 + z->re, 360 + z->im, 0x00FFFFFF);
// 		if (point_inside_window(540 + z2->re, 360 + z2->im, 1080, 720))
// 			my_mlx_pixel_put(data, 540 + z2->re, 360 + z2->im, 0x007070FF);
// 		if (point_inside_window(540 + z3->re, 360 + z3->im, 1080, 720))
// 			my_mlx_pixel_put(data, 540 + z3->re, 360 + z3->im, 0x00FF7070);
// 		if (point_inside_window(540 + z4->re, 360 + z4->im, 1080, 720))
// 			my_mlx_pixel_put(data, 540 + z4->re, 360 + z4->im, 0x0070FF70);
// 		step += 0.001;
// 	}
// }

t_complex *set_offset(t_complex *z, long double shift_x, long double shift_y)
{
	set_complex(z, z->re + shift_x, z->im + shift_y);
	return (z);
}

void	mandelbrot_iteration(t_complex *z, t_complex *c) // z^2 + c
{
	long double tmp_re;

	tmp_re = z->re;
	z->re = z->re * z->re - z->im * z->im + c->re;
	z->im = 2 * tmp_re * z->im + c->im;
}

void	z_2_p_c(t_complex *z, t_complex *c) // z^2 + c
{
	long double tmp_re;

	tmp_re = z->re;
	z->re = z->re * z->re - z->im * z->im + c->re;
	z->im = 2 * tmp_re * z->im + c->im;
}

void	z_3_p_c(t_complex *z, t_complex *c) // z^3 + c
{
	long double tmp_re;

	tmp_re = z->re;
	z->re = (z->re * z->re * z->re) - 3 * (z->re * z->im * z->im) + c->re;
	z->im = 3 * (tmp_re * tmp_re * z->im) - (z->im * z->im * z->im) + c->im;
}

void	z_4_p_c(t_complex *z, t_complex *c) // z^4 + c
{
	long double tmp_re;

	tmp_re = z->re;
	z->re = (z->re * z->re * z->re * z->re) - 6 * (z->re * z->re * z->im * z->im) + (z->im * z->im * z->im * z->im) + c->re;
	z->im = 4 * tmp_re * z->im * (tmp_re * tmp_re - z->im * z->im) + c->im;
}

void	_3_z_2(t_complex *z) // 3z^2
{
	long double tmp_re;

	tmp_re = z->re;
	z->re = 3 * (z->re * z->re - z->im * z->im);
	z->im = 6 * tmp_re * z->im;
}

void	_4_z_3(t_complex *z) // 4z^3
{
	long double tmp_re;

	tmp_re = z->re;
	z->re = 4 * (z->re * z->re * z->re) - 12 * (z->re * z->im * z->im);
	z->im = 12 * (tmp_re * tmp_re * z->im) - 4 * (z->im * z->im * z->im);
}

// void	mandelbrot_iteration2(t_complex *z, t_complex *c)
// {
// 	long double tmp_re;

// 	tmp_re = z->re;
// 	z->re = z->re * z->re * z->re - 3 * z->re * z->im * z->im + c->re;
// 	z->im = 3 * z->re * z->re * z->im - z->im * z->im * z->im + c->im;
// }

// int	check_point_mandelbrot(t_complex *c, int max_iterations)
// {
// 	t_complex *z = init_complex(0, 0);
// 	int	i;

// 	i = -1;
// 	while (++i < max_iterations)
// 	{
// 		if (z->re * z->re + z->im * z->im > 225)
// 			break ;
// 		mandelbrot_iteration2(z, c);
// 	}
// 	return (i);
// }

int	color_from_iterations(int iterations, int max_iterations)
{
	int	intensity;
	intensity = round(0xFF * sqrt((double)iterations / max_iterations));
	return (intensity + (intensity << 8) + (intensity << 16)); // color in rgb: (intensity, intensity, intensity)
}

int	mandelbrot(t_complex *c) // point -> color of that point in mandelbrot set
{
	int max_iterations = 1024;
	int iterations;
	t_complex *z = init_complex(0, 0);

	// if ((c->re + 1) * (c->re + 1) + c->im * c->im < 0.0625)
	// 	return (0x000000);
	// z = dekart_to_polar(z, c->re - 0.25, c->im);
	// if (0.5 * (1 - cos(z->im)) > z->re)
	// 	return (0x000000);
	// set_complex(z, 0, 0);

	iterations = -1;
	while (++iterations < max_iterations)
	{
		if (z->im * z->im + z->re * z->re > 4)
			break ;
		z_2_p_c(z, c);
	}

	if (iterations == max_iterations)
		return (0x000000); // black
	
	return (color_from_iterations(iterations, max_iterations));
}

int	julia(t_complex *z) // point -> color of that point in julia set
{
	int max_iterations = 1024;
	int iterations;
	t_complex *c = init_complex(0.28, 0.0113);
	// long double r = (1 + sqrt(1 + 4 * hypot(c->im, c->re))) / 2;

	iterations = -1;
	while (++iterations < max_iterations)
	{
		if (z->im * z->im + z->re * z->re > 4)
			break ;
		z_2_p_c(z, c);
	}

	// printf("%d", iterations);

	if (iterations == max_iterations)
		return (0x000000); // black
	return (color_from_iterations(iterations, max_iterations));
}

void	newton_iteraion(t_complex *z)
{
	static t_complex *c = 0;
	static t_complex *f_z = 0;
	static t_complex *fp_z = 0;
	static t_complex *dev = 0;

	if (c == 0)
	{
		c = init_complex(-1, 0);
		f_z = init_complex(z->re, z->im);
		fp_z = init_complex(z->re, z->im);
		dev = init_complex(0, 0);
	}
	else
	{
		f_z = set_complex(f_z, z->re, z->im);
		fp_z = set_complex(fp_z, z->re, z->im);
	}

	z_4_p_c(f_z, c);
	_4_z_3(fp_z);
	dev = set_complex(dev,
		(f_z->re * fp_z->re + f_z->im * fp_z->im) / (fp_z->re * fp_z->re + fp_z->im * fp_z->im),
		(fp_z->re * f_z->im - fp_z->im * f_z->re) / (fp_z->re * fp_z->re + fp_z->im * fp_z->im)
	);

	z->re = z->re - dev->re;
	z->im = z->im - dev->im;
}

int	newton(t_complex *z)
{
	int max_iterations = 64;
	int iterations;
	double epsilon = 0.00001;
	t_complex *z1 = init_complex(0, 0);
	// t_complex *c = init_complex(-1, 0);

	iterations = -1;
	while (++iterations < max_iterations)
	{
		z1 = set_complex(z1, z->re, z->im);
		newton_iteraion(z);
	}

	// if (z->re > 0.25)
	// 	return (0xFF0000);
	// else if (z->im > 0)
	// 	return (0x00FF00);
	// else
	// 	return (0x0000FF);

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

void	fill_coord_plane(t_mlx_data *data)
{
	int	color;
	t_complex *z = init_complex(0, 0);

	int	x;
	int	y;
	x = -1;
	while (++x < data->width)
	{
		y = -1;
		while (++y < data->height)
		{
			z = set_complex(z, (x - data->shift_x) * data->scale, (y - data->shift_y) * data->scale);
			// color = mandelbrot(z);
			// color = julia(z);
			color = newton(z);
			// if (x > 798)
			// 	printf("(238) here %d %d\n", x, y);
			my_mlx_pixel_put(data->img, x, y, color);
		}
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}

// int	loop_animation(t_mlx_data *data)
// {
// 	static int color = 0x00000000;
// 	int current_color;
// 	int x;
// 	int y;

// 	y = -1;
// 	while (++y < 720)
// 	{
// 		x = -1;
// 		while (++x < 1080)
// 		{
// 			current_color = color;
// 			current_color += 0x00010000 * (x * 0xFF / 1080);
// 			current_color += 0x00000001 * (y * 0xFF / 720);
// 			my_mlx_pixel_put(data->img, x, y, current_color);
// 		}
// 	}
// 	color += 255;
// 	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
// 	return (0);
// }
void	clear_window(t_mlx_data *data)
{
	int x;
	int y;

	x = -1;
	while (++x < data->width)
	{
		y = -1;
		while (++y < data->height)
		{
			my_mlx_pixel_put(data->img, x, y, 0x000000);
		}
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}

int key_num(int key, t_mlx_data *data)
{
	printf("%d\n", key);
	if (key == 53)
		exit(0);
	else if (key == 1)
	{
		data->scale *= 1.2;
		
		data->shift_x -= data->width / 2;
		data->shift_x /= 1.2;
		data->shift_x += data->width / 2;

		data->shift_y -= data->height / 2;
		data->shift_y /= 1.2;
		data->shift_y += data->height / 2;
	}
	else if (key == 13)
	{
		data->scale *= 0.8;
		
		data->shift_x -= data->width / 2;
		data->shift_x /= 0.8;
		data->shift_x += data->width / 2;

		data->shift_y -= data->height / 2;
		data->shift_y /= 0.8;
		data->shift_y += data->height / 2;
	}
	else if (key == 123)
		data->shift_x += 40;
	else if (key == 124)
		data->shift_x -= 40;
	else if (key == 125)
		data->shift_y -= 40;
	else if (key == 126)
		data->shift_y += 40;
	
	if (key == 49)
		fill_coord_plane(data);
	
	// fill_coord_plane(data);

	return (0);
}

int	main(int ac, char **av)
{
	t_mlx_data	*data;
	
	data = (t_mlx_data *)malloc(sizeof(t_mlx_data));
	data->img = (t_data *)malloc(sizeof(t_data));

	data->width = 800;
	data->height = 600;
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, data->width, data->height, "fractol");
	data->img->img = mlx_new_image(data->mlx, data->width, data->height);
	data->img->addr = mlx_get_data_addr(data->img->img, &data->img->bits_per_pixel, &data->img->line_length, &data->img->endian);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
	data->scale = 0.003;
	data->shift_x = data->width / 2;
	data->shift_y = data->height / 2;
	fill_coord_plane(data);

	mlx_key_hook(data->mlx_win, key_num, data);
	mlx_loop(data->mlx);
}
