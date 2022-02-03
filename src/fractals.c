#include "fractol.h"

static int	color_from_iterations(int iterations, int max_iterations)
{
	int	intensity;

	intensity = round(0xFF * sqrt((double)iterations / max_iterations));
	return (intensity + (intensity << 8) + (intensity << 16)); // color in rgb: (intensity, intensity, intensity)
}

int	mandelbrot(t_mlx_data *data, t_complex *c)
{
	void		(*formula)(t_complex *, t_complex *);
	const int	max_iterations = 1024;
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
	return (color_from_iterations(iterations, max_iterations));
}

int	julia(t_mlx_data *data, t_complex *z)
{
	void		(*formula)(t_complex *, t_complex *);
	const int	max_iterations = 1024;
	int			iterations;
	t_complex	*c;

	c = data->point; // 0.28 0.0113
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
	return (color_from_iterations(iterations, max_iterations));
}

int	ship(t_mlx_data *data, t_complex *c)
{
	const int	max_iterations = 1024;
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
	return (color_from_iterations(iterations, max_iterations));
}
