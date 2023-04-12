/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:48:11 by ulayus            #+#    #+#             */
/*   Updated: 2023/04/12 10:35:08 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"

void	init_direction_vectors(t_mlx *mlx)
{
	mlx->config->pos_x = mlx->config->y;
	mlx->config->pos_y = mlx->config->x;
	mlx->config->dir_x = 0;
	mlx->config->dir_y = 0;
	if (mlx->config->orientation == 'N')
		mlx->config->dir_y = -1;
	else if (mlx->config->orientation == 'S')
		mlx->config->dir_y = 1;
	else if (mlx->config->orientation == 'E')
		mlx->config->dir_x = 1;
	else if (mlx->config->orientation == 'W')
		mlx->config->dir_x = -1;
}

void	init_raycast(t_mlx *mlx)
{
	double	dir_x;
	double	dir_y;

	dir_x = 0;
	dir_y = 0;
	if (mlx->config->orientation == 'N')
		dir_y = -1;
	else if (mlx->config->orientation == 'S')
		dir_y = 1;
	else if (mlx->config->orientation == 'E')
		dir_x = 1;
	else if (mlx->config->orientation == 'W')
		dir_x = -1;
	mlx->config->plane_x = -(dir_y) * 0.66;
	mlx->config->plane_y = dir_x * 0.66;
}

void	set_icon(t_mlx *mlx, t_texture *config)
{
	mlx->icon = mlx_load_xpm42("assets/biden.xpm42");
	if (mlx->icon == NULL)
		free_render_exit(config, mlx, "icon error\n");
	mlx_set_icon(mlx->init, &mlx->icon->texture);
	mlx_delete_xpm42(mlx->icon);
}

void	init_side_dist_in_dda(t_dda *dda, t_mlx *mlx, t_raycast *info)
{
	if (info->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (mlx->config->pos_x - dda->map_x)
			* dda->delta_dist_x;
	}
	else
		dda->side_dist_x = (dda->map_x + 1.0 - mlx->config->pos_x)
			* dda->delta_dist_x;
	if (info->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (mlx->config->pos_y - dda->map_y)
			* dda->delta_dist_y;
	}
	else
		dda->side_dist_y = (dda->map_y + 1.0 - mlx->config->pos_y)
			* dda->delta_dist_y;
}

void	init_dda(t_dda *dda, t_raycast *info, t_mlx *mlx)
{
	dda->map_x = (int)(mlx->config->pos_x);
	dda->map_y = (int)(mlx->config->pos_y);
	if (info->ray_dir_x == 0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = ft_abs(1 / info->ray_dir_x);
	if (info->ray_dir_y == 0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = ft_abs(1 / info->ray_dir_y);
	dda->step_x = 1;
	dda->step_y = 1;
	init_side_dist_in_dda(dda, mlx, info);
}
