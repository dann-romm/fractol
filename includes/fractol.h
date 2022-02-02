#ifndef FRACTOL_H
# define FRACTOL_H

# define ABS(x) ((x) > 0 ? (x) : -(x))

# include <math.h>
# include <stdlib.h>
# include <stdio.h>

#include <string.h> // strcmp

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_complex
{
	long double	re;
	long double	im;
}				t_complex;

typedef struct	s_mlx_data
{
	void		*mlx;
	void		*mlx_win;
	t_data		*img;

	int			width;
	int			height;
	int			shift_x;
	int			shift_y;
	long double	scale;
	char		fractal_type; // m, j, s, n
	int			power; // 2, 3, 4, 5
	t_complex	*point;
}				t_mlx_data;

// fractol.c
int			color_from_iterations(int iterations, int max_iterations);

// complex.c
t_complex	*init_complex(long double re, long double im);
t_complex	*set_complex(t_complex *z, long double re, long double im);

// utils.c
void		*choose_fractal(char fractal_type);
void		*choose_formula(int power);

// farctals.c
int			mandelbrot(t_mlx_data *data, t_complex *z);
int			julia(t_mlx_data *data, t_complex *z);
int			ship(t_mlx_data *data, t_complex *z);
int			newton(t_mlx_data *data, t_complex *z);

// functions.c
void		_2_z(t_complex *z); // 2z
void		z_2_p_c(t_complex *z, t_complex *c); // z^2 + c
void		abs_z_2_p_c(t_complex *z, t_complex *c); // |z|^2 + c
void		z_3_p_c(t_complex *z, t_complex *c); // z^3 + c
void		z_4_p_c(t_complex *z, t_complex *c); // z^4 + c
void		_3_z_2(t_complex *z); // 3z^2
void		_4_z_3(t_complex *z); // 4z^3

#endif