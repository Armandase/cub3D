/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:11:45 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/21 17:13:07 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"

void	rotate_vectors(t_mlx *mlx, int flag)
{
	double			angle;
	const double	dir_x = mlx->config->dir_x;
	const double	dir_y = mlx->config->dir_y;
	const double	plane_x = mlx->config->plane_x;
	const double	plane_y = mlx->config->plane_y;

	angle = ROTATION_SPEED * (M_1_PI / 180.0);
	if (flag == LEFT)
		angle = -angle;
	mlx->config->dir_x = cos(angle) * dir_x - sin(angle) * dir_y;
	mlx->config->dir_y = sin(angle) * dir_x + cos(angle) * dir_y;
	mlx->config->plane_x = cos(angle) * plane_x - sin(angle) * plane_y;
	mlx->config->plane_y = sin(angle) * plane_x + cos(angle) * plane_y;
}

void	no_so_movement(int *key, t_mlx *mlx, double tmp_dir_x, double tmp_dir_y)
{
	if (*key == 'w')
	{
		if (mlx->config->map[(int)mlx->config->pos_y]
			[(int)(mlx->config->pos_x + tmp_dir_x)] == '0')
			mlx->config->pos_x += tmp_dir_x;
		if (mlx->config->map[(int)(mlx->config->pos_y + tmp_dir_y)]
			[(int)mlx->config->pos_x] == '0')
			mlx->config->pos_y += tmp_dir_y;
	}
	if (*key == 's')
	{
		if (mlx->config->map[(int)mlx->config->pos_y]
			[(int)(mlx->config->pos_x - tmp_dir_x)] == '0')
			mlx->config->pos_x -= tmp_dir_x;
		if (mlx->config->map[(int)(mlx->config->pos_y - tmp_dir_y)]
			[(int)mlx->config->pos_x] == '0')
			mlx->config->pos_y -= tmp_dir_y;
	}
}

void	ea_we_movement(int *key, t_mlx *mlx,
		double tmp_plane_x, double tmp_plane_y)
{
	if (*key == 'd')
	{
		if (mlx->config->map[(int)mlx->config->pos_y]
			[(int)(mlx->config->pos_x + tmp_plane_x)] == '0')
			mlx->config->pos_x += tmp_plane_x;
		if (mlx->config->map[(int)(mlx->config->pos_y + tmp_plane_y)]
			[(int)mlx->config->pos_x] == '0')
			mlx->config->pos_y += tmp_plane_y;
	}
	if (*key == 'a')
	{
		if (mlx->config->map[(int)mlx->config->pos_y]
			[(int)(mlx->config->pos_x - tmp_plane_x)] == '0')
			mlx->config->pos_x -= tmp_plane_x;
		if (mlx->config->map[(int)(mlx->config->pos_y - tmp_plane_y)]
			[(int)mlx->config->pos_x] == '0')
			mlx->config->pos_y -= tmp_plane_y;
	}
}

int	handle_key(int key, t_mlx *mlx)
{
	double	tmp_dir_x;
	double	tmp_dir_y;
	double	tmp_plane_x;
	double	tmp_plane_y;

	tmp_dir_x = mlx->config->dir_x * MOVEMENT_SPEED;
	tmp_dir_y = mlx->config->dir_y * MOVEMENT_SPEED;
	tmp_plane_x = mlx->config->plane_x * MOVEMENT_SPEED;
	tmp_plane_y = mlx->config->plane_y * MOVEMENT_SPEED;
	if (key == XK_Escape)
		destroy_win(mlx);
	if (key == 'a' || key == 'd' || key == 'w' || key == 's'
		|| key == XK_Left || key == XK_Right)
	{
		no_so_movement(&key, mlx, tmp_dir_x, tmp_dir_y);
		ea_we_movement(&key, mlx, tmp_plane_x, tmp_plane_y);
		if (key == XK_Left)
			rotate_vectors(mlx, LEFT);
		if (key == XK_Right)
			rotate_vectors(mlx, RIGHT);
		raycasting(mlx);
	}
	return (0);
}
