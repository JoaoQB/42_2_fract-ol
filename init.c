/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:18:33 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/03/11 13:50:39 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	malloc_error(void)
{
	perror("Problems with malloc");
	exit(EXIT_FAILURE);
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
	fractal->img.mlx_img = mlx_new_image(fractal->mlx_ptr, WIDTH, HEIGHT);
	if (fractal->img.mlx_img == NULL)
	{
		mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
		mlx_destroy_display(fractal->mlx_ptr);
		free(fractal->mlx_ptr);
		malloc_error();
	}
	fractal->img.addr = mlx_get_data_addr(fractal->img.mlx_img,
			&fractal->img.bpp, &fractal->img.line_len, &fractal->img.endian);
	// printf("bpp: %d\n", fractal->img.bpp);
	// printf("line_len: %d\n", fractal->img.line_len);
	// printf("endian: %d\n", fractal->img.endian);
	// printf("Image address: %p\n", fractal->img.addr);

	// events_init() // TODO
	// data_init() // TODO
}
