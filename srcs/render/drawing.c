#include "../../includes/render.h"

size_t	get_color_from_img(mlx_image_t *img, int x, int y)
{
	uint32_t	color;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;

	r = img->pixels[(y * img->width + x) * 4];
	g = img->pixels[(y * img->width + x) * 4 + 1];
	b = img->pixels[(y * img->width + x) * 4 + 2];
	color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	printf("Color: %d\n", color);
	return (color);
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
		mlx_put_pixel(mlx->img, x, y, color);
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
