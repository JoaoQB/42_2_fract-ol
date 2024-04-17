/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:27:28 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/04/17 10:47:22 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strcmp(const char *str, const char *str2)
{
	int	i;

	i = 0;
	if (str == NULL || str2 == NULL)
		return (0);
	while (str[i] && str2[i] && str[i] == str2[i])
		i++;
	return (str[i] - str2[i]);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL || fd < 0)
		return ;
	if (*s != '\0')
	{
		write(fd, s, sizeof(char));
		ft_putstr_fd(s + 1, fd);
	}
}

double	ft_atodbl(char *s)
{
	long	int_part;
	double	fract_part;
	double	pow;
	int		sign;

	int_part = 0;
	fract_part = 0;
	pow = 1;
	sign = 1;
	while ((*s >= '\t' && *s <= '\r') || 32 == *s)
		++s;
	while ('+' == *s || '-' == *s)
		if ('-' == *s++)
			sign = -sign;
	while ((*s >= '0' && *s <= '9') && *s && *s != '.')
		int_part = (int_part * 10) + (*s++ - '0');
	if ('.' == *s)
		++s;
	while ((*s >= '0' && *s <= '9') && *s)
	{
		pow /= 10;
		fract_part = fract_part + (*s++ - '0') * pow;
	}
	return ((int_part + fract_part) * sign);
}
