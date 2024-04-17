/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:20:00 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/04/17 10:46:35 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	rescale(double unscaled_num, double new_min, double new_max, double old_min, double old_max)
{
	return ((new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min) + new_min);
}

t_complex	sum_complex(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.x = z1.x + z2.x;
	result.yi = z1.yi + z2.yi;
	return (result);
}

t_complex	square_complex(t_complex z)
{
	t_complex	result;

	result.x = (z.x * z.x) - (z.yi * z.yi);
	result.yi = 2 * z.x * z.yi;
	return (result);
}
