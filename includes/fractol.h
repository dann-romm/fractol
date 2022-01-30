#ifndef FRACTOL_H
# define FRACTOL_H

# define ABS(x) ((x) > 0 ? (x) : -(x))

# include <math.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

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
	void		(*func)(t_complex *, void (*f)(t_complex *, t_complex *));
}				t_mlx_data;

typedef struct	s_color
{
	int	color;
}				t_color;

typedef struct	s_complex
{
	long double	re;
	long double	im;
}				t_complex;

void	_2_z(t_complex *z); // 2z
void	z_2_p_c(t_complex *z, t_complex *c); // z^2 + c
void	z_3_p_c(t_complex *z, t_complex *c); // z^3 + c
void	z_4_p_c(t_complex *z, t_complex *c); // z^4 + c
void	_3_z_2(t_complex *z); // 3z^2
void	_4_z_3(t_complex *z); // 4z^3

#endif