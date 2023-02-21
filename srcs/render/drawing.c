# include "../../includes/render.h"

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

void	iter_in_sprite(t_raycast *info, double tex_pos, double step, t_mlx *mlx, t_dda *dda, int x, int tex_x)
{
	int	y;
	int	tex_y;
	int	color;

	y = info->start;
	while (y < info->end)
	{
		tex_y = (int)tex_pos % (63);
		tex_pos += step;
		color = mlx->config->img_tab[dda->orientation][tex_y][tex_x];
		if (dda->side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&(mlx->img), x, y, color);
		y++;
	}
}

void	put_sprite_to_img(t_mlx *mlx, int x, t_dda *dda, t_raycast *info)
{
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;

	if (dda->side == 0)
		wall_x = mlx->config->posY + dda->perpWallDist * info->rayDirY;
	else
		wall_x = mlx->config->posX + dda->perpWallDist * info->rayDirX;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * 64.0);
	if (dda->side == 0 && info->rayDirX > 0)
		tex_x = 64.0 - tex_x - 1;
	if (dda->side == 1 && info->rayDirY < 0)
		tex_x = 64.0 - tex_x - 1;
	step = 1.0 * 64 / (info->end - info->start);
	tex_pos = (info->start - HEIGHT / 2 + (info->end - info->start) / 2) * step;
	iter_in_sprite(info, tex_pos, step, mlx, dda, x, tex_x);
}
