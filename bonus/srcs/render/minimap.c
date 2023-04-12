/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:26:00 by adamiens          #+#    #+#             */
/*   Updated: 2023/04/11 15:24:16 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"

void	draw_square(t_mlx *mlx, int x, int y, long int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SQUARE_SIZE)
	{
		j = 0;
		while (j < SQUARE_SIZE)
		{
			mlx_put_pixel(mlx->img,
				x * SQUARE_SIZE + i, y * SQUARE_SIZE + j, color);
			j++;
		}
		i++;
	}
}

void	minimap(t_mlx *mlx)
{
	int	x;
	int	y;

	y = 0;
	while (mlx->config->map[y])
	{
		x = 0;
		while (mlx->config->map[y][x])
		{
			if (mlx->config->map[y][x] == '1')
				draw_square(mlx, x, y, 255000000);
			else if (mlx->config->map[y][x] == 'D')
				draw_square(mlx, x, y, 0x00ff00ff);
			else if (mlx->config->map[y][x] == 'd')
				draw_square(mlx, x, y, 0x9acd32ff);
			else if (mlx->config->map[y][x] == '\n')
				break ;
			else
				draw_square(mlx, x, y, 255);
			x++;
		}
		y++;
	}
	draw_square(mlx,
		(int)mlx->config->pos_x, (int)mlx->config->pos_y, 0xFF0000FF);
}
