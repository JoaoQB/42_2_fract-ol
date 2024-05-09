/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:20:00 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/05/09 12:44:42 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	fill_mandel(t_complex *z)
{
	z->csquare = (z->x * z->x) + (z->yi * z->yi);
	if ((256.0 * z->csquare * z->csquare - 96.0
			* z->csquare + 32.0 * z->x - 3.0 < 0.0)
		|| (16.0 * (z->csquare +2.0 * z->x + 1.0) - 1.0 < 0.0))
		return (1);
	else
		return (0);
}

double	rescale(double num, int flag)
{
	if (flag == 1)
		return ((2 - -2) * (num - 0) / (WIDTH - 0) + -2);
	else
		return ((-2 - 2) * (num - HEIGHT) / (0 - HEIGHT) + 2);
}

double	rescale_color(double num, t_fractal *fractal)
{
	return ((fractal->cmin - fractal->cmax)
		* (num - 0) / (fractal->iter_definition - 0) + fractal->cmax);
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
