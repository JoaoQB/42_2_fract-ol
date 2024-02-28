/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:22:50 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/02/28 14:33:38 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot_equation(void)
{
	t_complex	z;
	t_complex	c;
	int			iter;
	double		tmp_real;

	z.real = 0;
	z.i = 0;

	c.real = 0.25;
	c.i = 0.4;

	iter = 0;
	while (iter < 42)
	{
		//General Formula
		// z = z² + c;

		tmp_real = (z.real * z.real) - (z.i * z.i); // same as x² - y²

		z.i = 2 * z.real * z.i; // same as 2xyi

		z.real = tmp_real;

		//Adding the c value
		z.real += c.real;
		z.i += c.i;

		printf("iteration n -> %d real %f imaginary %f\n", iter, z.real, z.i);
		iter++;
	}
}
