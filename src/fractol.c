/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:47:01 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/05 19:30:27 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	usage(void)
{
	printf("\
Fractol - This project is meant to create beautiful fractals\n\n\
usage: ./fractol <argument>\n\n\
Arguments:\n\
   -m [power]         Mandelbroth fractal with power 2 to 4\n\
   -j [power] [x y]   Julia fractal with power 2 to 4 from starting point\n\
   -n                 Newton fractal\n\
   -s                 Burning ship fractal\n\
   -h                 Print Help (this message) and exit\n\n\
Controls:\n\
   arrows             Movement along the coordinate plane\n\
   W, S, mouse wheel  Zoom in and out\n\
   A, D               Color shifting\n\n\
");
	exit(0);
}

void	fill_coord_plane(t_mlx_data *data)
{
	int			(*fractal)(t_mlx_data *, t_complex *);
	t_complex	*z;
	int			x;
	int			y;

	z = init_complex(0, 0);
	if (!z)
		errnomem_exit("fractol");
	fractal = choose_fractal(data->fractal_type);
	x = (data->x_bound < 0) * (WIDTH + data->x_bound) - 1;
	while (++x < WIDTH - (data->x_bound > 0) * (WIDTH - data->x_bound))
	{
		y = (data->y_bound < 0) * (HEIGHT + data->y_bound) - 1;
		while (++y < HEIGHT - (data->y_bound > 0) * (HEIGHT - data->y_bound))
		{
			z = set_complex(z, (x - data->shift_x) * data->scale,
					(y - data->shift_y) * data->scale);
			ft_mlx_pixel_put(data->img, x, y, fractal(data, z));
		}
	}
	free(z);
	data->x_bound = 0;
	data->y_bound = 0;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}

void	parsing(t_mlx_data *data, int ac, char **av)
{
	if (ac > 1 && (!ft_strcmp(av[1], "-m") || !ft_strcmp(av[1], "-j")
			|| !ft_strcmp(av[1], "-s") || !ft_strcmp(av[1], "-n")))
		data->fractal_type = av[1][1];
	else
		usage();
	set_complex(data->point, 0, 0);
	if (data->fractal_type == 'm' || data->fractal_type == 'j')
	{
		if (ac > 2)
		{
			data->power = ft_atoi(av[2]);
			if (data->fractal_type == 'j' && ac == 5)
				set_complex(data->point, ft_atof(av[3]), ft_atof(av[4]));
			else if (data->fractal_type == 'j' && ac == 4)
				usage();
		}
		else
			data->power = 2;
		if (data->power < 2 || data->power > 4
			|| (data->fractal_type == 'm' && ac > 3))
			usage();
	}
}

void	data_init(t_mlx_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fractol");
	data->img->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img->addr = mlx_get_data_addr(data->img->img,
			&data->img->bits_per_pixel,
			&data->img->line_length,
			&data->img->endian);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
	data->scale = 0.003;
	data->shift_x = WIDTH / 2;
	data->shift_y = HEIGHT / 2;
	data->x_bound = 0;
	data->y_bound = 0;
	data->color_mode = 7;
}

int	main(int ac, char **av)
{
	t_mlx_data	*data;

	if (ac == 1)
		usage();
	data = (t_mlx_data *)malloc(sizeof(t_mlx_data));
	if (!data)
		errnomem_exit("fractol");
	data->img = (t_data *)malloc(sizeof(t_data));
	data->point = (t_complex *)malloc(sizeof(t_complex));
	if (!data->img || !data->point)
		errnomem_exit("fractol");
	parsing(data, ac, av);
	data_init(data);
	fill_coord_plane(data);
	mlx_hook(data->mlx_win, 4, 0, mouse_hook, data);
	mlx_key_hook(data->mlx_win, key_hook, data);
	mlx_loop(data->mlx);
}
