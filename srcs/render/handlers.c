/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:57:50 by ulayus            #+#    #+#             */
/*   Updated: 2023/04/11 14:58:42 by ulayus           ###   ########.fr       */
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

bool	check_cell(char cell, t_texture *config)
{
	if (cell == '0' || cell == config->orientation || cell == 'd')
		return (true);
	return (false);
}

static void	change_pos(t_mlx *mlx, double offset_x, double offset_y)
{
	if (check_cell(mlx->config->map[(int)mlx->config->pos_y]
			[(int)(mlx->config->pos_x + offset_x)], mlx->config) == true)
		mlx->config->pos_x += offset_x;
	if (check_cell(mlx->config->map[(int)(mlx->config->pos_y + offset_y)]
		[(int)mlx->config->pos_x], mlx->config) == true)
		mlx->config->pos_y += offset_y;
}

static void	handle_movement(t_mlx *mlx)
{
	double	tmp_dir_x;
	double	tmp_dir_y;
	double	tmp_plane_x;
	double	tmp_plane_y;

	tmp_dir_x = mlx->config->dir_x * MOVEMENT_SPEED;
	tmp_dir_y = mlx->config->dir_y * MOVEMENT_SPEED;
	tmp_plane_x = mlx->config->plane_x * MOVEMENT_SPEED;
	tmp_plane_y = mlx->config->plane_y * MOVEMENT_SPEED;
	if (mlx_is_key_down(mlx->init, MLX_KEY_W))
		change_pos(mlx, tmp_dir_x, tmp_dir_y);
	if (mlx_is_key_down(mlx->init, MLX_KEY_S))
		change_pos(mlx, -tmp_dir_x, -tmp_dir_y);
	if (mlx_is_key_down(mlx->init, MLX_KEY_D))
		change_pos(mlx, tmp_plane_x, tmp_plane_y);
	if (mlx_is_key_down(mlx->init, MLX_KEY_A))
		change_pos(mlx, -tmp_plane_x, -tmp_plane_y);
}

void	handle_key(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	handle_movement(mlx);
	if (mlx_is_key_down(mlx->init, MLX_KEY_ESCAPE))
		mlx_close_window(mlx->init);
	if (mlx_is_key_down(mlx->init, MLX_KEY_LEFT))
		rotate_vectors(mlx, LEFT);
	if (mlx_is_key_down(mlx->init, MLX_KEY_RIGHT))
		rotate_vectors(mlx, RIGHT);
	if (mlx_is_key_down(mlx->init, MLX_KEY_SPACE))
	{
		mlx->config->anim = 1;
		system("paplay assets/biden_su.ogg &");
	}
	mouse_hook_camera(mlx);
	raycasting(mlx);
}
