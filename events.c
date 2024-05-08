/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:20:27 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/05/08 11:20:12 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// int	handle_mouse(int button, int x, int y, t_fractal *fractal)
// {
// 	if (button == Button4)
// 		fractal->zoom *= 0.95;
// 	else if (button == Button5)
// 		fractal->zoom *= 1.05;
// 	fractal_render(fractal);
// 	return (0);
// }
static double interpolate(double start, double end, double interpolation)
{
    return start + ((end - start) * interpolation);
}

// Function to apply smooth zoom
static void applyZoom(t_fractal* fractal, double mouseRe, double mouseIm, double zoomFactor)
{
     double interpolation = 1.0 / zoomFactor;
     fractal->re_min = interpolate(mouseRe, fractal->re_min, interpolation);
     fractal->im_min = interpolate(mouseIm, fractal->im_min, interpolation);
     fractal->re_max = interpolate(mouseRe, fractal->re_max, interpolation);
     fractal->im_max = interpolate(mouseIm, fractal->im_max, interpolation);
	 fractal->zoom /= zoomFactor;
}

int handle_mouse(int button, int x, int y, t_fractal *fractal)
{
    double mouseRe, mouseIm;
    mouseRe = (double)x / (WIDTH / (fractal->re_max - fractal->re_min)) + fractal->re_min;
    mouseIm = (double)y / (HEIGHT / (fractal->im_max - fractal->im_min)) + fractal->im_min;

    if (button == Button4)
        applyZoom(fractal, mouseRe, mouseIm, 1.01); // Smooth zoom in
    else if (button == Button5)
        applyZoom(fractal, mouseRe, mouseIm, 1.0 / 1.01); // Smooth zoom out

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
	fractal_render(fractal);
	return (0);
}
