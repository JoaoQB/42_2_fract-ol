/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pollock.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:49:25 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/02/21 09:57:30 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <X11/keysym.h>

#define WIDTH 500
#define HEIGHT 500

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
} t_data;

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

int	handle_no_event(void *data)
{
	return (0);
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}

int	main(void)
{
	t_data	data;
	int		x;
	int		y;
	int		encoded_color;

	srand(time(NULL));
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr,
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
			mlx_pixel_put(data.mlx_ptr,
							data.win_ptr,
							x,
							y,
							rand() % 0x1000000);
			x++;
		}
		y++;
	}
	encoded_color = encode_rgb(255, 125, 64);
	mlx_string_put(data.mlx_ptr,
					data.win_ptr,
					WIDTH * 0.8,
					HEIGHT * 0.95,
					encoded_color,
					"My pollock");
	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_key_hook(data.win_ptr, &handle_input, &data);

	mlx_loop(data.mlx_ptr);
	/* Exit the loop if there's no window, execute this code */
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
