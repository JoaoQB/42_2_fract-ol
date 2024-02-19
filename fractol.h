/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:58:23 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/02/19 14:12:07 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <stdint.h> // Define integer types, limits, macros
# include <stdlib.h> // Memory allocation
# include <stdio.h> // Printf

# define WIDTH 500
# define HEIGHT 500
# define MLX_ERROR 1
# define RED_PIXEL 0x00FF0000
# define GREEN_PIXEL 0x0000FF00
# define BLUE_PIXEL 0x000000FF

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
} t_data;

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue);

#endif
