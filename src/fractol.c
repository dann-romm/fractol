#include "mlx.h"
#include "fractol.h"

void	usage(void)
{
	printf("\
Fractol - This project is meant to create beautiful fractals\n\n\
usage: ./fractol <argument>\n\n\
Arguments:\n\
   -m [power]        Mandelbroth fractal with power 2 to 5\n\
   -j [power] <x y>  Julia fractal with power 2 to 5 from starting point\n\
   -n [power]        Newton fractal with power 2 to 5\n\
   -s                Burning ship fractal\n\
   -h                Print Help (this message) and exit\n\n\
");
	exit(0);
}

void	ft_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_color(t_data *img, int x, int y)
{
	unsigned int	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*dst);
}

void	make_shift(t_mlx_data *data, int dx, int dy)
{
	int	color;
	int	x;
	int	y;

	if (dx > 0)
	{
		y = 0;
		while (y < data->height)
		{
			x = dx;
			while (x < data->width)
			{
				ft_mlx_pixel_put(data->img, x, y, get_color(data->img, x - dx, y));
			}
			y++;
		}
	}
}

int	color_from_iterations(int iterations, int max_iterations)
{
	int	intensity;

	intensity = round(0xFF * sqrt((double)iterations / max_iterations));
	return (intensity + (intensity << 8) + (intensity << 16)); // color in rgb: (intensity, intensity, intensity)
}

void	fill_coord_plane(t_mlx_data *data)
{
	int			color;
	t_complex	*z;
	int			(*fractal)(t_mlx_data *, t_complex *);
	int			x;
	int			y;

	z = init_complex(0, 0);
	if (!z)
		return ; // exit with error
	fractal = choose_fractal(data->fractal_type);
	x = -1;
	while (++x < data->width)
	{
		y = -1;
		while (++y < data->height)
		{
			z = set_complex(z, (x - data->shift_x) * data->scale, (y - data->shift_y) * data->scale);
			color = fractal(data, z);
			ft_mlx_pixel_put(data->img, x, y, color);
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
		data->scale *= 1.6;
		
		data->shift_x -= data->width / 2;
		data->shift_x /= 1.6;
		data->shift_x += data->width / 2;

		data->shift_y -= data->height / 2;
		data->shift_y /= 1.6;
		data->shift_y += data->height / 2;
	}
	else if (key == 13)
	{
		data->scale *= 0.625;
		
		data->shift_x -= data->width / 2; // TODO: shift сделай нормальный оптимизированный клянусь ежжи
		data->shift_x /= 0.625;
		data->shift_x += data->width / 2;

		data->shift_y -= data->height / 2;
		data->shift_y /= 0.625;
		data->shift_y += data->height / 2;
	}
	else if (key == 123)
		data->shift_x += 80;
	else if (key == 124)
		data->shift_x -= 80;
	else if (key == 125)
		data->shift_y -= 80;
	else if (key == 126)
		data->shift_y += 80;
	
	if (key == 49)
		fill_coord_plane(data);
	
	// fill_coord_plane(data);

	return (0);
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

int	main(int ac, char **av)
{
	t_mlx_data	*data;

	if (ac == 1)
		usage();
	data = (t_mlx_data *)malloc(sizeof(t_mlx_data));
	data->img = (t_data *)malloc(sizeof(t_data));
	data->point = (t_complex *)malloc(sizeof(t_complex));
	parsing(data, ac, av);
	printf("point: (%Lf; %Lf)\n", data->point->re, data->point->im);
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
