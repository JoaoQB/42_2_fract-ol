/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jqueijo- <jqueijo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:46:49 by jqueijo-          #+#    #+#             */
/*   Updated: 2024/02/09 14:56:46 by jqueijo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minilibx-linux/mlx.h"

int	main(void)
{
	void	*mlx_connection;

	mlx_connection = mlx_init();
	mlx_destroy_display(mlx_connection);
	free(mlx_connection);
}
