/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:58:23 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/03/15 14:22:22 by jqueijo-         ###   ########.fr       */
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
	double	zoom;
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
int		mandelbrot_equation(void);

/* string_utils.c */
int		ft_strcmp(const char *str, const char *str2);
void	ft_putstr_fd(char *s, int fd);

/* math_utils.c */
double		rescale(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);

/* init.c */
void	fractal_init(t_fractal *fractal);
// void	data_init(t_fractal *fractal);
// void	events_init(t_fractal *fractal);

/* render.c */
void	fractal_render(t_fractal *fractal);

/* events.c */
int		handle_keypress(int keysym, t_fractal *fractal);
int		handle_close(t_fractal *fractal);
int		handle_mouse(int button, int x, int y, t_fractal  *fractal);



#endif
