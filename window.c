/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:46:49 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/02/19 13:14:38 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		encoded_color;

	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		return (MLX_ERROR);
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "my_window");
	if (win_ptr == NULL)
	{
		free(mlx_ptr);
		return (MLX_ERROR);
	}
	encoded_color = encode_rgb(255, 128, 64);
	printf("Encoded RGB color: %06X\n", encoded_color);
	mlx_pixel_put(mlx_ptr, win_ptr, WIDTH / 2, HEIGHT / 2, encoded_color);
	mlx_loop(mlx_ptr);
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
}
