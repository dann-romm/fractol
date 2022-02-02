#include "fractol.h"

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

static void	newton_iteraion(t_complex *z)
{
	static t_complex	*c = 0;
	static t_complex	*f_z = 0;
	static t_complex	*fp_z = 0;
	static t_complex	*dev = 0;

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
	set_complex(dev, (f_z->re * fp_z->re + f_z->im * fp_z->im) / (fp_z->re
			* fp_z->re + fp_z->im * fp_z->im), (fp_z->re * f_z->im - fp_z->im
			* f_z->re) / (fp_z->re * fp_z->re + fp_z->im * fp_z->im));
	z->re = z->re - dev->re;
	z->im = z->im - dev->im;
}

int	newton(t_mlx_data *data, t_complex *z)
{
	const int		max_iterations = 64;
	int				iterations;
	const double	epsilon = 0.00001;
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
