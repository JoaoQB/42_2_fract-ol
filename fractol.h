/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:58:23 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/02/26 10:46:45 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <stdint.h> // Define integer types, limits, macros
# include <stdlib.h> // Memory allocation
# include <stdio.h> // Printf
# include <X11/keysym.h> // Predefined key symbols corresponding to keycodes
# include <X11/X.h> // Constant definitions for Xlib functions

# define WIDTH 600
# define HEIGHT 300
# define MLX_ERROR 1
# define RED_PIXEL 0x00FF0000
# define GREEN_PIXEL 0x0000FF00
# define BLUE_PIXEL 0x000000FF
# define WHITE_PIXEL 0x00FFFFFF

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
} t_rect;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; // Bits per pixel
	int		line_len;
	int		endian;
} t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
} t_data;

int		encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
int		handle_no_event(void *data);
// int	handle_input(int keysym, t_data *data);
// int	handle_keyrelease(int keysym, t_data *data);
int		handle_keypress(int keysym, t_data *data);
int		render(t_data *data);
int		render_rect(t_img *img, t_rect rect);
void	render_background(t_img *img, int color);

#endif
