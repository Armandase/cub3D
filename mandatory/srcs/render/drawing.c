/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:14:07 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/21 17:14:08 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	if (x <= WIDTH && x >= 0 && y <= HEIGHT && y >= 0)
	{
		dest = data->addr + (y * data->line_len + x *(data->bits_per_px / 8));
		*(unsigned int *)dest = color;
	}
}

size_t	get_color_from_img(t_data *data, int x, int y)
{
	int		offset;
	size_t	ret;
	int		r;
	int		g;
	int		b;

	offset = (y * data->line_len + x * (data->bits_per_px / 8));
	r = data->addr[offset + 2];
	g = data->addr[offset + 1];
	b = data->addr[offset];
	ret = (r << 16) + (g << 8) + b;
	return (ret);
}

void	iter_in_sprite(t_raycast *info, t_mlx *mlx, t_dda *dda, int x)
{
	int	y;
	int	tex_y;
	int	color;

	y = info->start;
	while (y < info->end)
	{
		tex_y = (int)info->tex_pos % (63);
		info->tex_pos += info->step;
		color = mlx->config->img_tab[dda->orientation][tex_y][info->tex_x];
		if (dda->side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&(mlx->img), x, y, color);
		y++;
	}
}

void	put_sprite_to_img(t_mlx *mlx, int x, t_dda *dda, t_raycast *info)
{
	double	wall_x;

	if (dda->side == 0)
		wall_x = mlx->config->pos_y + dda->perp_wall_dist * info->ray_dir_y;
	else
		wall_x = mlx->config->pos_x + dda->perp_wall_dist * info->ray_dir_x;
	wall_x -= floor(wall_x);
	info->tex_x = (int)(wall_x * 64.0);
	if (dda->side == 0 && info->ray_dir_x > 0)
		info->tex_x = 64.0 - info->tex_x - 1;
	if (dda->side == 1 && info->ray_dir_y < 0)
		info->tex_x = 64.0 - info->tex_x - 1;
	info->step = 1.0 * 64 / (double)dda->wall_height;
	info->tex_pos = (info->start - (double)HEIGHT / 2
			+ (double)dda->wall_height / 2) * info->step;
	iter_in_sprite(info, mlx, dda, x);
}
