/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:18:33 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/03/15 10:26:58 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	malloc_error(void)
{
	perror("Problems with malloc");
	exit(EXIT_FAILURE);
}

void	data_init(t_fractal *fractal)
{
	fractal->iter_definition = 1000;
	fractal->escape_value = 4;
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


	// events_init() // TODO
	data_init(fractal);
}
