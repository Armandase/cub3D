/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:14:14 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/21 17:14:16 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"

double	ft_abs(double nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
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

static void	free_texture(t_texture *config)
{
	if (config->no != NULL)
		ft_free((void *)&config->no);
	if (config->so != NULL)
		ft_free((void *)&config->so);
	if (config->we != NULL)
		ft_free((void *)&config->we);
	if (config->ea != NULL)
		ft_free((void *)&config->ea);
	ft_free_strs(config->map);
}

int	destroy_win(t_mlx *mlx)
{
	mlx_loop_end(mlx->init);
	mlx_destroy_image(mlx->init, mlx->img.img);
	mlx_clear_window(mlx->init, mlx->win);
	mlx_destroy_window(mlx->init, mlx->win);
	mlx_destroy_display(mlx->init);
	free_texture(mlx->config);
	free(mlx->init);
	exit (0);
	return (0);
}
