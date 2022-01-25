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
	void	*mlx;
	void	*mlx_win;
	t_data	*img;
	int		width;
	int		height;
	int		shift_x;
	int		shift_y;
	long double	scale;
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

#endif