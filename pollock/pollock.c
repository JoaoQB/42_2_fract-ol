/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pollock.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:49:25 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/02/19 13:29:22 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define WIDTH 500
#define HEIGHT 500

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window;
	int		x;
	int		y;
	int		encoded_color;

	srand(time(NULL));
	mlx_connection = mlx_init();
	mlx_window = mlx_new_window(mlx_connection,
								WIDTH,
								HEIGHT,
								"my first window");
	x = 0;
	y = HEIGHT * 0.1;
	while (y < HEIGHT * 0.9)
	{
		x = WIDTH * 0.1;
		while (x < WIDTH * 0.9)
		{
			mlx_pixel_put(mlx_connection,
							mlx_window,
							x,
							y,
							rand() % 0x1000000);
			x++;
		}
		y++;
	}
	encoded_color = encode_rgb(255, 125, 64);
	mlx_string_put(mlx_connection,
					mlx_window,
					WIDTH * 0.8,
					HEIGHT * 0.95,
					encoded_color,
					"My pollock");
	mlx_loop(mlx_connection);
	mlx_destroy_display(mlx_connection);
	mlx_destroy_window(mlx_connection, mlx_window);
	free(mlx_connection);
	free(mlx_window);
}
