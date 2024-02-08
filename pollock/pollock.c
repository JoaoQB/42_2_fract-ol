/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pollock.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:49:25 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/02/08 13:36:24 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"

#define WIDTH 500
#define HEIGHT 500

int	main(void)
{
	void	*mlx_connection;
	void	*mlx_window;
	int		x;
	int		y;

	mlx_connection = mlx_init();
	mlx_window = mlx_new_window(mlx_connection,
								500,
								500,
								"my first window");
	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_pixel_put(mlx_connection,
							mlx_window,
							x,
							y,
							0x00ACA6);
			x++;
		}
		y++;
	}
	mlx_loop(mlx_connection);
}
