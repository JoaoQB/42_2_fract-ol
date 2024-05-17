/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:02:53 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/05/17 12:55:14 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if ((argc == 2 && !ft_strcmp(argv[1], "mandelbrot"))
		|| ((!ft_strcmp(argv[1], "julia")) && (argc == 2 || argc == 4)))
	{
		fractal.name = argv[1];
		if (argv[2] && argv[3])
		{
			fractal.julia_x = ft_atodbl(argv[2]);
			fractal.julia_yi = ft_atodbl(argv[3]);
		}
		else
		{
			fractal.julia_x = 0.285;
			fractal.julia_yi = 0.01;
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_ptr);
	}
	else
	{
		ft_putstr_fd(ERROR_MESSAGE, STDOUT_FILENO);
		exit(EXIT_FAILURE);
	}
}
