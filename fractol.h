/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:58:23 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/05/08 14:08:43 by jqueijo-         ###   ########.fr       */
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
'./fractol mandelbrot' for Mandelbrot set\n\
'./fractol julia' for pre-determined Julia set\n\
'./fractol julia <re_value> <im_value>' for a custom Julia set\n\n\
Press p and m to change the number of iterations (plus and minus)\n\
Use the mouse wheel to zoom in and out\n\
Use the arrow keys to move the image\n\
Press c to change the color range\n"

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
