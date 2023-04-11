#include "../../includes/render.h"

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

bool	check_wall(t_mlx *mlx, t_dda *dda)
{
	bool		hit;
	const char	tile = mlx->config->map[dda->map_y][dda->map_x];

	hit = false;
	if (dda->map_x > -1 && dda->map_y > -1
		&& (tile == '1' || tile == 'D' || tile == 'd'))
	{
		hit = true;
		pthread_mutex_lock(&mlx->config->door_opened_mtx);	
		if (mlx->config->door_opened == true && mlx->config->middle == true)
		{
			if (mlx->config->map[dda->map_y][dda->map_x] == 'D')
				mlx->config->map[dda->map_y][dda->map_x] = 'd';
			else if (mlx->config->map[dda->map_y][dda->map_x] == 'd')
			{
				mlx->config->map[dda->map_y][dda->map_x] = 'D';
				hit = false;
			}
			mlx->config->door_opened = false;
		}
		pthread_mutex_unlock(&mlx->config->door_opened_mtx);	
		if (mlx->config->map[dda->map_y][dda->map_x] == 'D')
			mlx->config->door = true;
		else if (mlx->config->map[dda->map_y][dda->map_x] == 'd')
			hit = false;
	}
	return (hit);
}

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
		mlx->config->middle = false;
		if (i == WIDTH / 2)
			mlx->config->middle = true;
		mlx->config->door = false;
		camera = 2 * i / (double)WIDTH - 1;
		info.ray_dir_x = mlx->config->dir_x + mlx->config->plane_x * camera;
		info.ray_dir_y = mlx->config->dir_y + mlx->config->plane_y * camera;
		send_rays(mlx, &info, &dda);
		draw_line(mlx, info, i, &dda);
		i++;
	}
	minimap(mlx);
	anim(mlx);
	hourglass(mlx);
}
