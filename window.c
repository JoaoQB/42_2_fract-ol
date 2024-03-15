/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:46:49 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/03/15 09:13:12 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

void	img_pix_put_basic(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* Big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* Little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i) & 0xFF);
		i -= 8;
	}
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
			img_pix_put(img, j++, i, color);
		++i;
	}
}

int	render_rect(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (MLX_ERROR);
	render_background(&data->img, WHITE_PIXEL);
	render_rect(&data->img, (t_rect){WIDTH - 100, HEIGHT - 100, 100, 100, GREEN_PIXEL});
	render_rect(&data->img, (t_rect){0, 0, 100, 100, RED_PIXEL});
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "My window!");
	if (data.win_ptr == NULL)
	{
		mlx_destroy_display(data.mlx_ptr);
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	data.img.img_ptr = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.img_ptr, &data.img.bpp, &data.img.line_len, &data.img.endian);
	printf("bpp: %d\n", data.img.bpp);
	printf("line_len: %d\n", data.img.line_len);
	printf("endian: %d\n", data.img.endian);
	printf("Image address: %p\n", data.img.addr);

	/* Setup Hooks */
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);

	/* Exit the loop if there's no window, execute this code */
	mlx_destroy_image(data.mlx_ptr, data.img.img_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
