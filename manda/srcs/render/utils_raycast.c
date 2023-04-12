/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:23:07 by ulayus            #+#    #+#             */
/*   Updated: 2023/04/12 10:36:33 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"

bool	check_wall(t_mlx *mlx, t_dda *dda)
{
	bool		hit;
	const char	tile = mlx->config->map[dda->map_y][dda->map_x];

	hit = false;
	if (dda->map_x > -1 && dda->map_y > -1 && tile == '1')
		hit = true;
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
