/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:58:23 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/03/12 14:09:05 by jqueijo-         ###   ########.fr       */
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
	void	*mlx_ptr; // mlx_init()
	void	*win_ptr; // mlx_new_window()
	t_img	img;

	//Hooks member variables
} t_fractal;

typedef struct s_complex
{
	double	real;
	double	i;
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
int		handle_keypress(int keysym, t_data *data);
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

/* init.c */
void	fractal_init(t_fractal *fractal);





#endif
