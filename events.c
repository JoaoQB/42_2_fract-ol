/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:20:27 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/05/08 14:08:27 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	else if (keysym == XK_p && fractal->iter_definition <= 502)
		fractal->iter_definition += 10;
	else if (keysym == XK_m && fractal->iter_definition >= 10)
		fractal->iter_definition -= 10;
	else if (keysym == XK_c)
		change_color_range(fractal);
	fractal_render(fractal);
	return (0);
}
