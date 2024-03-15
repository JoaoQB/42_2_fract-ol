/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugg_onepagecode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:41:20 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/03/15 13:49:30 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <stdint.h> // Define integer types, limits, macros
# include <stdlib.h> // Memory allocation
# include <stdio.h> // Standard input and output, perror function / Debugging
# include <math.h>
# include <unistd.h> // System calls
# include <X11/keysym.h> // Predefined key symbols corresponding to keycodes
# include <X11/X.h> // Constant definitions for Xlib functions

# define ERROR_MESSAGE "Please enter \n\t\"./fractol mandelbrot\" or \n\t\"./fractol julia <n value> <ni value>\"\n"
# define MLX_ERROR 1

# define WIDTH 800
# define HEIGHT 800

# define RED_PIXEL 0x00FF0000
# define GREEN_PIXEL 0x0000FF00
# define BLUE_PIXEL 0x000000FF
# define WHITE_PIXEL 0x00FFFFFF

#define BLACK 0x000000
#define WHITE 0xFFFFFF
#define PURPLE 0x800080
#define TEAL 0x008080
#define MAGENTA 0xFF00FF
#define LIME 0x00FF00
#define CYAN 0x00FFFF
#define YELLOW 0xFFFF00
#define ORANGE 0xFFA500
#define HOT_PINK 0xFF69B4
#define AQUAMARINE 0x7FFFD4
#define INDIGO 0x4B0082

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
} t_img;

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
} t_fractal;

typedef struct s_complex
{
	double	x;
	double	yi;
} t_complex;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
} t_rect;


typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
} t_data;

/* window.c */
int		encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
int		handle_keypress2(int keysym, t_data *data);
void	img_pix_put_basic(t_img *img, int x, int y, int color);
void	img_pix_put(t_img *img, int x, int y, int color);
void	render_background(t_img *img, int color);
int		render_rect(t_img *img, t_rect rect);
int		render(t_data *data);

/* equation.c */
int	mandelbrot_equation(void);

/* string_utils.c */
int	ft_strcmp(const char *str, const char *str2);
void	ft_putstr_fd(char *s, int fd);

/* math_utils.c */
double	rescale(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);

/* init.c */
void	fractal_init(t_fractal *fractal);
// void	data_init(t_fractal *fractal);
// void	events_init(t_fractal *fractal);

/* render.c */
void	fractal_render(t_fractal *fractal);

/* events.c */
int	handle_keypress(int keysym, t_fractal *fractal);




#endif

int	handle_keypress(int keysym, t_fractal *fractal)
{
	// if (keysym == XK_Escape)
	// 	handle_close(fractal);
	if (keysym == XK_Left)
		fractal->shift_x += 0.05;
	else if (keysym == XK_Right)
		fractal->shift_x -= 0.05;
	// else if (keysym == XK_Up)
	// 	??
	// else if (keysym == XK_Down)
	// 	??
	else if (keysym == XK_plus)
		fractal->iter_definition += 10;
	else if (keysym == XK_minus)
		fractal->iter_definition -= 10;

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
}

static void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->win_ptr, KeyPress, KeyPressMask, &handle_keypress, fractal);
	// mlx_hook(fractal->win_ptr, ButtonPress, ButtonPressMask, &handle_mouse, &fractal);// TODO
	// mlx_hook(fractal->win_ptr, DestroyNotify, StructureNotifyMask, &handle_close, &fractal);// TODO
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

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.x = 0;
	z.yi = 0;
	c.x = rescale(x, -2, 2, 0, WIDTH) + fractal->shift_x;
	c.yi = rescale(y, 2, -2, HEIGHT, 0) + fractal->shift_y;

	while (i < fractal->iter_definition)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.yi * z.yi) > fractal->escape_value)
		{
			color = rescale(i, WHITE, BLACK, 0, fractal->iter_definition);
			my_pix_put(&fractal->img, x, y, color);
			return ;
		}
		i++;
	}
	my_pix_put(&fractal->img, x, y, BLACK);
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

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if ((argc == 2 && !ft_strcmp(argv[1], "mandelbrot"))
		|| (argc == 4 && !ft_strcmp(argv[1], "julia")))
	{
		fractal.name = argv[1];
		fractal_init(&fractal);
		fractal_render(&fractal);
		printf("rendered");
		mlx_loop(fractal.mlx_ptr);
		mlx_destroy_image(fractal.mlx_ptr, fractal.img.img_ptr);
		mlx_destroy_display(fractal.mlx_ptr);
		free(fractal.mlx_ptr);
	}
	else
	{
		ft_putstr_fd(ERROR_MESSAGE, STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
}
