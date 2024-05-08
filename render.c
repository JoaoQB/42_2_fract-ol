/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:52:55 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/05/08 14:50:11 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	double		csquare;
	// static double	xy[HEIGHT]; TODO!!!!
	// // i = -1;
	// // if (xy[0] == 0)
	// // {
	// // 	while (++i < HEIGHT)
	// // 		xy[i] = ((-(HEIGHT + HEIGHT) + 4 * i) / HEIGHT);
	// // }
	// // z.x = (xy[x] * fractal->zoom) + fractal->shift_y;
	// // z.yi = (xy[y] * fractal->zoom) + fractal->shift_y;
	z.x = (rescale(x, -2, 2, 0, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.yi = (rescale(y, 2, -2, HEIGHT, 0) * fractal->zoom) + fractal->shift_y;
	csquare = (z.x * z.x) + (z.yi * z.yi);
	if ((256.0 * csquare * csquare - 96.0 * csquare + 32.0 * z.x - 3.0 < 0.0 )
	|| (16.0 * (csquare +2.0 * z.x + 1.0) - 1.0 < 0.0))
		return (my_pix_put(&fractal->img, x, y, fractal->cmin));
	julia_vs_mandel(&z, &c, fractal);
	i = 0;
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
