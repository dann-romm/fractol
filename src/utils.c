#include "fractol.h"

void	*choose_fractal(char fractal_type)
{
	if (fractal_type == 'm')
		return (*mandelbrot);
	else if (fractal_type == 'j')
		return (*julia);
	else if (fractal_type == 's')
		return (*ship);
	else if (fractal_type == 'n')
		return (*newton);
	else
		return (0);
}

void	*choose_formula(int power)
{
	if (power == 2)
		return (*z_2_p_c);
	else if (power == 3)
		return (*z_3_p_c);
	else if (power == 4)
		return (*z_4_p_c);
	else
		return (0);
}

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
