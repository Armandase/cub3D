/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:01:48 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/21 17:02:30 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"

t_dda	*apply_dda(t_mlx *mlx, t_raycast *info, t_dda *dda)
{
	bool	hit;

	init_dda(dda, info, mlx);
	hit = false;
	while (hit == false)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (mlx->config->map[dda->map_y]
			&& mlx->config->map[dda->map_y][dda->map_x] != '0')
			hit = true;
	}
	return (dda);
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

void	send_rays(t_mlx *mlx, t_raycast *info, t_dda *dda)
{
	apply_dda(mlx, info, dda);
	if (dda->side == 0)
		dda->perp_wall_dist = dda->side_dist_x - dda->delta_dist_x;
	else
		dda->perp_wall_dist = dda->side_dist_y - dda->delta_dist_y;
	dda->wall_height = (int)((double)HEIGHT / dda->perp_wall_dist);
	info->start = -(dda->wall_height) / 2 + HEIGHT / 2;
	if (info->start < 0)
		info->start = 0;
	info->end = dda->wall_height / 2 + HEIGHT / 2;
	if (info->end >= HEIGHT)
		info->end = HEIGHT - 1;
	dda->orientation = select_texture(info, *dda, dda->side);
}

void	draw_line(t_mlx *mlx, t_raycast info, int line, t_dda *dda)
{
	const int	x = line;
	int			y;

	y = 0;
	while (y <= HEIGHT)
	{
		if (y < info.start)
			my_mlx_pixel_put(&(mlx->img), x, y, mlx->config->floor);
		else if (y >= info.start && y <= info.end)
		{
			put_sprite_to_img(mlx, x, dda, &info);
			y = info.end;
		}
		else if (y > info.end)
			my_mlx_pixel_put(&(mlx->img), x, y, mlx->config->ceiling);
		y++;
	}
}

void	raycasting(t_mlx *mlx)
{
	t_raycast	info;
	double		camera;
	t_dda		dda;
	int			i;

	i = 0;
	while (i <= WIDTH)
	{
		camera = 2 * i / (double)WIDTH - 1;
		info.ray_dir_x = mlx->config->dir_x + mlx->config->plane_x * camera;
		info.ray_dir_y = mlx->config->dir_y + mlx->config->plane_y * camera;
		send_rays(mlx, &info, &dda);
		draw_line(mlx, info, i, &dda);
		i++;
	}
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img.img, 0, 0);
}
