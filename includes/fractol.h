/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:56:58 by doalbaco          #+#    #+#             */
/*   Updated: 2022/02/05 17:22:12 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define SHIFT_LENGTH 40
# define WIDTH 800
# define HEIGHT 600

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "mlx.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_complex
{
	long double	re;
	long double	im;
}				t_complex;

typedef struct s_mlx_data
{
	void		*mlx;
	void		*mlx_win;
	t_data		*img;
	int			shift_x;
	int			shift_y;
	int			x_bound;
	int			y_bound;
	long double	scale;
	char		fractal_type;
	int			power;
	t_complex	*point;
	int			color_mode;
}				t_mlx_data;

// utils_mlx.c
void		ft_mlx_pixel_put(t_data *img, int x, int y, int color);
int			get_color(t_data *img, int x, int y);
int			key_hook(int key, t_mlx_data *data);
int			mouse_hook(int key, int x, int y, t_mlx_data *data);

// fractol.c
void		fill_coord_plane(t_mlx_data *data);

// complex.c
t_complex	*init_complex(long double re, long double im);
t_complex	*set_complex(t_complex *z, long double re, long double im);

// utils.c
void		*choose_fractal(char fractal_type);
void		*choose_formula(int power);
double		abs_double(double a);

// utils_ft.c
int			ft_atoi(const char *str);
double		ft_atof(const char *str);
int			ft_strcmp(char *s1, char *s2);

// farctals.c
int			mandelbrot(t_mlx_data *data, t_complex *z);
int			julia(t_mlx_data *data, t_complex *z);
int			ship(t_mlx_data *data, t_complex *z);

// fractals_newton.c
int			newton(t_mlx_data *data, t_complex *z);

// functions.c
void		z_2_p_c(t_complex *z, t_complex *c); // z^2 + c
void		abs_z_2_p_c(t_complex *z, t_complex *c); // |z|^2 + c
void		z_3_p_c(t_complex *z, t_complex *c); // z^3 + c
void		z_4_p_c(t_complex *z, t_complex *c); // z^4 + c
void		_4_z_3(t_complex *z); // 4z^3

// shift.c
void		right_shift(t_mlx_data *data, int dx, int dy);
void		left_shift(t_mlx_data *data, int dx, int dy);
void		zoom_in(t_mlx_data *data, int x, int y);
void		zoom_out(t_mlx_data *data, int x, int y);

#endif