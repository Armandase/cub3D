/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:23:07 by ulayus            #+#    #+#             */
/*   Updated: 2023/04/11 14:23:30 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"

void	check_door(t_mlx *mlx, t_dda *dda, char tile, bool *hit)
{
	pthread_mutex_lock(&mlx->config->door_opened_mtx);
	if (mlx->config->door_opened == true && mlx->config->middle == true)
	{
		if (tile == 'D')
			mlx->config->map[dda->map_y][dda->map_x] = 'd';
		else if (tile == 'd')
		{
			mlx->config->map[dda->map_y][dda->map_x] = 'D';
			*hit = false;
		}
		mlx->config->door_opened = false;
	}
	pthread_mutex_unlock(&mlx->config->door_opened_mtx);
}

bool	check_wall(t_mlx *mlx, t_dda *dda)
{
	bool		hit;
	const char	tile = mlx->config->map[dda->map_y][dda->map_x];

	hit = false;
	if (dda->map_x > -1 && dda->map_y > -1
		&& (tile == '1' || tile == 'D' || tile == 'd'))
	{
		hit = true;
		check_door(mlx, dda, tile, &hit);
		if (tile == 'D')
			mlx->config->door = true;
		else if (tile == 'd')
			hit = false;
	}
	return (hit);
}

int	select_texture(t_raycast *info, t_dda dda, int side)
{
	int	orientation;

	if (info->end >= HEIGHT)
		info->end = HEIGHT - 1;
	if (dda.step_x == -1 && side == 0)
		orientation = WEST;
	else if (dda.step_x == 1 && side == 0)
		orientation = EAST;
	else if (dda.step_y == 1 && side == 1)
		orientation = NORTH;
	else
		orientation = SOUTH;
	return (orientation);
}
