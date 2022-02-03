#include "fractol.h"

void	fill_coord_plane(t_mlx_data *data)
{
	int			(*fractal)(t_mlx_data *, t_complex *);
	int			color;
	t_complex	*z;
	int			x;
	int			y;

	z = init_complex(0, 0);
	if (!z)
		return ; // exit with error
	fractal = choose_fractal(data->fractal_type);
	x = (data->x_bound < 0) * (WIDTH + data->x_bound) - 1;
	while (++x < WIDTH - (data->x_bound > 0) * (WIDTH - data->x_bound))
	{
		y = (data->y_bound < 0) * (HEIGHT + data->y_bound) - 1;
		while (++y < HEIGHT - (data->y_bound > 0) * (HEIGHT - data->y_bound))
		{
			z = set_complex(z, (x - data->shift_x) * data->scale, (y - data->shift_y) * data->scale);
			color = fractal(data, z);
			ft_mlx_pixel_put(data->img, x, y, color);
		}
	}
	data->x_bound = 0;
	data->y_bound = 0;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}

void	parsing(t_mlx_data *data, int ac, char **av) // strcmp atof atoi
{
	if (ac > 1 && (!strcmp(av[1], "-m") || !strcmp(av[1], "-j")
		|| !strcmp(av[1], "-s") || !strcmp(av[1], "-n")))
		data->fractal_type = av[1][1];
	else
		usage();
	if (data->fractal_type == 'm' || data->fractal_type == 'j'
		|| data->fractal_type == 'n')
	{
		if (ac < 3)
			usage();
		data->power = atoi(av[2]);
	}
	if (data->fractal_type == 'j')
	{
		if (ac < 5)
			usage();
		set_complex(data->point, atof(av[3]), atof(av[4]));
	}
	else
		set_complex(data->point, 0, 0);
}

void	data_init(t_mlx_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fractol");
	data->img->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img->addr = mlx_get_data_addr(data->img->img, &data->img->bits_per_pixel, &data->img->line_length, &data->img->endian);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
	data->scale = 0.003;
	data->shift_x = WIDTH / 2;
	data->shift_y = HEIGHT / 2;
	data->x_bound = 0;
	data->y_bound = 0;
}

int	main(int ac, char **av)
{
	t_mlx_data	*data;

	if (ac == 1)
		usage();
	data = (t_mlx_data *)malloc(sizeof(t_mlx_data));
	data->img = (t_data *)malloc(sizeof(t_data));
	data->point = (t_complex *)malloc(sizeof(t_complex));
	data_init(data);

	parsing(data, ac, av);
	printf("point: (%Lf; %Lf)\n", data->point->re, data->point->im);


	fill_coord_plane(data);

	mlx_hook(data->mlx_win, 4, 0, mouse_hook, data);
	mlx_key_hook(data->mlx_win, key_hook, data);
	mlx_loop(data->mlx);
}
