#include "../../includes/render.h"

void	swap_axes(u_int32_t ***array)
{
	int		x;
	int		y;
	size_t	tmp;

	x = 0;
	while (x < 64)
	{
		y = 0;
		while (y < x)
		{
			tmp = (*array)[x][y];
			(*array)[x][y] = (*array)[y][x];
			(*array)[y][x] = tmp;
			y++;
		}
		x++;
	}
}

void	copy_texture_from_img_to_array(t_texture *config,
		mlx_image_t *img, int i, t_mlx *mlx)
{
	int		x;
	int		y;

	x = 0;
	config->img_tab[i] = malloc(sizeof(size_t *) * 64);
	while (x < 64)
	{
		y = 0;
		config->img_tab[i][x] = malloc(sizeof(size_t) * 64);
		while (y < 64)
		{
			config->img_tab[i][x][y] = get_color_from_img(img, x, y);
			y = y + 1;
		}
		x = x + 1;
	}
	swap_axes(&config->img_tab[i]);
	if (img)
		mlx_delete_image(mlx->init, img);
}

void	texture_to_tab(t_texture *config, t_mlx *mlx)
{
	int			i;
	mlx_image_t	*img;
	xpm_t		*xpm;

	i = 0;
	while (i < 4)
	{
		if (i == 0)
			xpm = mlx_load_xpm42(config->no);
		else if (i == 1)
			xpm = mlx_load_xpm42(config->so);
		else if (i == 2)
			xpm = mlx_load_xpm42(config->ea);
		else if (i == 3)
			xpm = mlx_load_xpm42(config->we);
		img = mlx_texture_to_image(mlx->init, &xpm->texture);
		copy_texture_from_img_to_array(config, img, i, mlx);
		i++;
	}
}

/*
void	copy_texture_animation(t_texture *config,
		t_data *img, int i, t_mlx *mlx)
{
	int		x;
	int		y;

	x = 0;
	config->portal_frames[i] = malloc(sizeof(size_t *) * 64);
	while (x < 64)
	{
		y = 0;
		config->portal_frames[i][x] = malloc(sizeof(size_t) * 64);
		while (y < 64)
		{
			config->portal_frames[i][x][y] = get_color_from_img(img, x, y);
			y = y + 1;
		}
		x = x + 1;
	}
	swap_axes(&config->portal_frames[i]);
	if (img->img)
		mlx_destroy_image(mlx->init, img->img);
}

void	animation_sprite(t_texture *config, t_mlx *mlx)
{
	int		i;
	int		img_len_x;
	int		img_len_y;
	t_data	img;

	i = 0;
	while (i < 23)
	{
		img.img = mlx_xpm_file_to_image
			(mlx->init, config->frames[i], &img_len_x, &img_len_y);
		img.addr = mlx_get_data_addr (img.img, &img.bits_per_px,
				&img.line_len, &img.endian);
		copy_texture_from_img_to_array(config, &img, i, mlx);
		i++;
	}
}

void	iter_in_sprite_animation(t_raycast *info, t_mlx *mlx, t_dda *dda, int x)
{
	int	y;
	int	tex_y;
	int	color;

	y = info->start;
	while (y < info->end)
	{
		tex_y = (int)info->tex_pos % (63);
		info->tex_pos += info->step;
		color = mlx->config->portal_frames[mlx->config->frame_id][tex_y][info->tex_x];
		if (dda->side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&(mlx->img), x, y, color);
		y++;
	}
}

void	put_sprite_to_img_animation(t_mlx *mlx, int x, t_dda *dda, t_raycast *info)
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
	iter_in_sprite_animation(info, mlx, dda, x);
}
*/
