# include "../../includes/render.h"

void	init_dda(t_dda *dda, t_raycast *info, t_mlx *mlx)
{
	dda->mapX = (int)(mlx->config->posX);
	dda->mapY = (int)(mlx->config->posY);
	if (info->rayDirX == 0)
		dda->deltaDistX = 1e30;
	else
		dda->deltaDistX = ft_abs(1 / info->rayDirX);
	if (info->rayDirY == 0)
		dda->deltaDistY = 1e30;
	else
		dda->deltaDistY = ft_abs(1 / info->rayDirY);
	dda->stepX = 1;
	dda->stepY = 1;
	if (info->rayDirX < 0)
	{
		dda->stepX = -1;
		dda->sideDistX = (mlx->config->posX - dda->mapX) * dda->deltaDistX;
	}
	else
		dda->sideDistX = (dda->mapX + 1.0 - mlx->config->posX) * dda->deltaDistX;
	if (info->rayDirY < 0)
	{
		dda->stepY = -1;
		dda->sideDistY = (mlx->config->posY - dda->mapY) * dda->deltaDistY;
	}
	else
		dda->sideDistY = (dda->mapY + 1.0 - mlx->config->posY) * dda->deltaDistY;
}

t_dda	*apply_dda(t_mlx *mlx, t_raycast *info, t_dda *dda)
{
	bool	hit;

	init_dda(dda, info, mlx);
	hit = false;
	while (hit == false)
	{
		if (dda->sideDistX < dda->sideDistY)
		{
			dda->sideDistX += dda->deltaDistX;
			dda->mapX += dda->stepX;
			dda->side = 0;
		}
		else
		{
			dda->sideDistY += dda->deltaDistY;
			dda->mapY += dda->stepY;
			dda->side = 1;
		}
		if (mlx->config->map[dda->mapY]
			&& mlx->config->map[dda->mapY][dda->mapX] != '0')
			hit = true;
	}
	return (dda);
}

int	select_texture(t_raycast *info, t_dda dda, int side)
{
	int	orientation;

	if (info->end >= HEIGHT)
		info->end = HEIGHT - 1;
	if (dda.stepX == -1 && side == 0)
		orientation = WEST;
	else if (dda.stepX == 1 && side == 0)
		orientation = EAST;
	else if (dda.stepY == 1 && side == 1)
		orientation = NORTH;
	else
		orientation = SOUTH;
	return (orientation);
}

void	send_rays(t_mlx *mlx, t_raycast *info, t_dda *dda)
{
	apply_dda(mlx, info, dda);
	if (dda->side == 0)
		dda->perpWallDist = dda->sideDistX - dda->deltaDistX;
	else
		dda->perpWallDist = dda->sideDistY - dda->deltaDistY;
	dda->wallHeight = (int)((double)HEIGHT / dda->perpWallDist);
	info->start = -(dda->wallHeight) / 2 + HEIGHT / 2;
	if (info->start < 0)
		info->start = 0;
	info->end = dda->wallHeight / 2 + HEIGHT / 2;
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
		info.rayDirX = mlx->config->dirX + mlx->config->planeX * camera;
		info.rayDirY = mlx->config->dirY + mlx->config->planeY * camera;
		send_rays(mlx, &info, &dda);
		draw_line(mlx, info, i, &dda);
		i++;
	}
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img.img, 0, 0);
}
