/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:20:15 by ulayus            #+#    #+#             */
/*   Updated: 2023/04/12 10:34:51 by ulayus           ###   ########.fr       */
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
		hit = check_wall(mlx, dda);
	}
	return (dda);
}

void	send_rays(t_mlx *mlx, t_raycast *info, t_dda *dda)
{
	apply_dda(mlx, info, dda);
	if (dda->side == 0)
		dda->perp_wall_dist = dda->side_dist_x - dda->delta_dist_x;
	else
		dda->perp_wall_dist = dda->side_dist_y - dda->delta_dist_y;
	if (dda->perp_wall_dist == 0)
		dda->perp_wall_dist = 1e30;
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
	while (y < HEIGHT)
	{
		if (y < info.start && (uint32_t)y < mlx->img->height
			&& (uint32_t)x < mlx->img->width)
			mlx_put_pixel(mlx->img, ft_abs(x), y, mlx->config->floor);
		else if (y >= info.start && y <= info.end
			&& (uint32_t)y < mlx->img->height && (uint32_t)x < mlx->img->width)
		{
			put_sprite_to_img(mlx, x, dda, &info);
			y = info.end;
		}
		else if (y > info.end && (uint32_t)y < mlx->img->height
			&& (uint32_t)x < mlx->img->width)
			mlx_put_pixel(mlx->img, ft_abs(x), y, mlx->config->ceiling);
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
}
