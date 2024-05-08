/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugg_onepagecode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:41:20 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/05/08 13:07:04 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <stdint.h> // Define integer types, limits, macros
# include <stdlib.h> // Memory allocation
# include <stdio.h> // Standard input and output, perror function / Debugging
# include <math.h> // math functions
# include <unistd.h> // System calls
# include <X11/keysym.h> // Predefined key symbols corresponding to keycodes
# include <X11/X.h> // Constant definitions for Xlib functions

# define ERROR_MESSAGE "Please enter:\n\n\
./fractol mandelbrot for Mandelbrot set\n\
./fractol julia for pre-determined Julia set\n\
./fractol julia <real_value> <imag_value> for a custom Julia set\n\n\
Press + and - to change the number of iterations\n\
Use the mouse wheel to zoom in and out\n\
Use the arrow keys to move the image\n"

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 512

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define PURPLE 0x800080
# define TEAL 0x008080
# define MAGENTA 0xFF00FF
# define LIME 0x00FF00
# define CYAN 0x00FFFF
# define YELLOW 0xFFFF00
# define ORANGE 0xFFA500
# define HOT_PINK 0xFF69B4
# define AQUAMARINE 0x7FFFD4
# define INDIGO 0x4B0082

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_fractal
{
	char	*name;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	int		iter_definition;
	int		escape_value;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_yi;
	double	fractal_type;
	double	cmin;
	double	cmax;
	int		color_range;
}	t_fractal;

typedef struct s_complex
{
	double	x;
	double	yi;
}	t_complex;

/* string_utils.c */
int			ft_strcmp(const char *str, const char *str2);
void		ft_putstr_fd(char *s, int fd);
double		ft_atodbl(char *s);

/* math_utils.c */
double		rescale(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);

/* init.c */
void		fractal_init(t_fractal *fractal);

/* render.c */
void		fractal_render(t_fractal *fractal);

/* events.c */
int			handle_keypress(int keysym, t_fractal *fractal);
int			handle_close(t_fractal *fractal);
int			handle_mouse(int button, int x, int y, t_fractal *fractal);

#endif


int	handle_mouse(int button, int x, int y, t_fractal *fractal)
{
	if (button == Button4)
		fractal->zoom *= 0.95;
	else if (button == Button5)
		fractal->zoom *= 1.05;
	fractal_render(fractal);
	return (0);
}

int	handle_close(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
	mlx_destroy_display(fractal->mlx_ptr);
	free(fractal->mlx_ptr);
	exit(EXIT_SUCCESS);
}

int	change_color_range(t_fractal *fractal)
{
	if (fractal->color_range == 1)
	{
		fractal->cmin = BLACK;
		fractal->cmax = WHITE;
		fractal->color_range = 2;
	}
	else if (fractal->color_range == 2)
	{
		fractal->cmin = WHITE;
		fractal->cmax = BLACK;
		fractal->color_range = 3;
	}
	else if (fractal->color_range == 3)
	{
		fractal->cmin = BLACK;
		fractal->cmax = ORANGE;
		fractal->color_range = 1;
	}
	return (0);
}

int	handle_keypress(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		handle_close(fractal);
	else if (keysym == XK_Left)
		fractal->shift_x += (0.05 * fractal->zoom);
	else if (keysym == XK_Right)
		fractal->shift_x -= (0.05 * fractal->zoom);
	else if (keysym == XK_Up)
		fractal->shift_y += (0.05 * fractal->zoom);
	else if (keysym == XK_Down)
		fractal->shift_y -= (0.05 * fractal->zoom);
	else if (keysym == XK_plus && fractal->iter_definition <= 502)
		fractal->iter_definition += 10;
	else if (keysym == XK_minus && fractal->iter_definition >= 10)
		fractal->iter_definition -= 10;
	else if (keysym == XK_c)
		change_color_range(fractal);
	fractal_render(fractal);
	return (0);
}

/* Normally one page */
static void	malloc_error(void)
{
	perror("Problems with malloc");
	exit(EXIT_FAILURE);
}

static void	data_init(t_fractal *fractal)
{
	fractal->iter_definition = 42;
	fractal->escape_value = 4;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
	fractal->cmin = BLACK;
	fractal->cmax = ORANGE;
	if (!ft_strcmp(fractal->name, "julia"))
		fractal->fractal_type = 2;
	else
		fractal->fractal_type = 1;
}

static void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->win_ptr, KeyPress,
		KeyPressMask, handle_keypress, fractal);
	mlx_hook(fractal->win_ptr, ButtonPress,
		ButtonPressMask, handle_mouse, fractal);
	mlx_hook(fractal->win_ptr, DestroyNotify,
		StructureNotifyMask, handle_close, fractal);
}

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_ptr = mlx_init();
	if (fractal->mlx_ptr == NULL)
		malloc_error();
	fractal->win_ptr = mlx_new_window(fractal->mlx_ptr, WIDTH,
			HEIGHT, fractal->name);
	if (fractal->win_ptr == NULL)
	{
		mlx_destroy_display(fractal->mlx_ptr);
		free(fractal->mlx_ptr);
		malloc_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_ptr, WIDTH, HEIGHT);
	if (fractal->img.img_ptr == NULL)
	{
		mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
		mlx_destroy_display(fractal->mlx_ptr);
		free(fractal->mlx_ptr);
		malloc_error();
	}
	fractal->img.addr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bpp, &fractal->img.line_len, &fractal->img.endian);
	events_init(fractal);
	data_init(fractal);
}

/* another page */
double	rescale(double unscaled_num, double new_min, double new_max, double old_min, double old_max)
{
	return ((new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min) + new_min);
}

t_complex	sum_complex(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.x = z1.x + z2.x;
	result.yi = z1.yi + z2.yi;
	return (result);
}

t_complex	square_complex(t_complex z)
{
	t_complex	result;

	result.x = (z.x * z.x) - (z.yi * z.yi);
	result.yi = 2 * z.x * z.yi;
	return (result);
}

/* another page */
static void	my_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i) & 0xFF);
		i -= 8;
	}
}

static void	julia_vs_mandel(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (fractal->fractal_type == 2)
	{
		c->x = fractal->julia_x;
		c->yi = fractal->julia_yi;
	}
	else
	{
		c->x = z->x;
		c->yi = z->yi;
	}
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.x = (rescale(x, -2, 2, 0, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.yi = (rescale(y, 2, -2, HEIGHT, 0) * fractal->zoom) + fractal->shift_y;
	julia_vs_mandel(&z, &c, fractal);
	while (i < fractal->iter_definition)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.yi * z.yi) > fractal->escape_value)
		{
			color = rescale(i, fractal->cmax, fractal->cmin, 0, fractal->iter_definition);
			my_pix_put(&fractal->img, x, y, color);
			return ;
		}
		i++;
	}
	my_pix_put(&fractal->img, x, y, fractal->cmin);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			handle_pixel(x, y, fractal);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr,
		fractal->img.img_ptr, 0, 0);
}

/* another page */

int	ft_strcmp(const char *str, const char *str2)
{
	int	i;

	i = 0;
	if (str == NULL || str2 == NULL)
		return (0);
	while (str[i] && str2[i] && str[i] == str2[i])
		i++;
	return (str[i] - str2[i]);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL || fd < 0)
		return ;
	if (*s != '\0')
	{
		write(fd, s, sizeof(char));
		ft_putstr_fd(s + 1, fd);
	}
}

double	ft_atodbl(char *s)
{
	long	int_part;
	double	fract_part;
	double	pow;
	int		sign;

	int_part = 0;
	fract_part = 0;
	pow = 1;
	sign = 1;
	while ((*s >= '\t' && *s <= '\r') || 32 == *s)
		++s;
	while ('+' == *s || '-' == *s)
		if ('-' == *s++)
			sign = -sign;
	while ((*s >= '0' && *s <= '9') && *s && *s != '.')
		int_part = (int_part * 10) + (*s++ - '0');
	if ('.' == *s)
		++s;
	while ((*s >= '0' && *s <= '9') && *s)
	{
		pow /= 10;
		fract_part = fract_part + (*s++ - '0') * pow;
	}
	return ((int_part + fract_part) * sign);
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if ((argc == 2 && !ft_strcmp(argv[1], "mandelbrot"))
		|| (!ft_strcmp(argv[1], "julia")) && (argc == 2 || argc == 4))
	{
		fractal.name = argv[1];
		if (argv[2] && argv[3])
		{
			fractal.julia_x = ft_atodbl(argv[2]);
			fractal.julia_yi = ft_atodbl(argv[3]);
		}
		else
		{
			fractal.julia_x = 0.285;
			fractal.julia_yi = 0.01;
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_ptr);
	}
	else
	{
		ft_putstr_fd(ERROR_MESSAGE, STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
}
