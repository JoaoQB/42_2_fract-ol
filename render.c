/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:52:55 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/05/09 12:45:48 by jqueijo-         ###   ########.fr       */
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

static void	cmp_scl(double st_x[WIDTH], double st_y[HEIGHT], t_fractal *fractal)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		st_x[i] = rescale(i, 1);
		i++;
	}
	i = 0;
	while (i < WIDTH)
	{
		st_y[i] = rescale(i, 2);
		i++;
	}
	fractal->first = 0;
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex		z;
	t_complex		c;
	int				i;
	static double	st_x[WIDTH];
	static double	st_y[HEIGHT];

	if (fractal->first == 1)
		cmp_scl(st_x, st_y, fractal);
	z.x = (st_x[x] * fractal->zoom) + fractal->shift_x;
	z.yi = (st_y[y] * fractal->zoom) + fractal->shift_y;
	if (fractal->fractal_type == 1 && fill_mandel(&z))
		return (my_pix_put(&fractal->img, x, y, fractal->cmin));
	julia_vs_mandel(&z, &c, fractal);
	i = -1;
	while (++i < fractal->iter_definition)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.yi * z.yi) > fractal->escape_value)
		{
			fractal->color = rescale_color(i, fractal);
			my_pix_put(&fractal->img, x, y, fractal->color);
			return ;
		}
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
