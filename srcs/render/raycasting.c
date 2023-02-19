# include "../../includes/render.h"

void	init_raycast(t_mlx *mlx, t_raycast *info)
{
	info->posX = (double)mlx->config->y;
	info->posY = (double)mlx->config->x;
	info->dirX = 0;
	info->dirY = 0;
	if (mlx->config->orientation == 'N')
		info->dirY = -1;
	else if (mlx->config->orientation == 'S')
		info->dirY = 1;
	else if (mlx->config->orientation == 'E')
		info->dirX = 1;
	else if (mlx->config->orientation == 'W')
		info->dirX = -1;
	info->planeX = -(info->dirY) * 0.66;
	info->planeY = info->dirX * 0.66;
}

void	init_dda(t_dda *dda, t_raycast *info)
{
	dda->mapX = (int)(info->posX);
	dda->mapY = (int)(info->posY);
	if (info->rayDirX == 0)
		dda->deltaDistX = 1e30;
	else
		dda->deltaDistX = ft_abs(1 / info->rayDirX);
		//dda->deltaDistX = sqrt(1 + pow(info->rayDirY, 2.0) / pow(info->rayDirX, 2.0));
	if (info->rayDirY == 0)
		dda->deltaDistY = 1e30;
	else
		dda->deltaDistY = ft_abs(1 / info->rayDirY);
		//dda->deltaDistY = sqrt(1 + pow(info->rayDirX, 2.0) / pow(info->rayDirY, 2.0));
	dda->stepX = 1;
	dda->stepY = 1;
	if (info->rayDirX < 0)
	{
		dda->stepX = -1;
		dda->sideDistX = (info->posX - dda->mapX) * dda->deltaDistX;
	}
	else
		dda->sideDistX = (dda->mapX + 1.0 - info->posX) * dda->deltaDistX;
	if (info->rayDirY < 0)
	{
		dda->stepY = -1;
		dda->sideDistY = (info->posY - dda->mapY) * dda->deltaDistY;
	}
	else
		dda->sideDistY = (dda->mapY + 1.0 - info->posY) * dda->deltaDistY;
}

int	apply_dda(t_mlx *mlx, t_raycast *info, t_dda *dda)
{
	bool	hit;
	int		side;

	init_dda(dda, info);
	hit = false;
	while (hit == false)
	{
		if (dda->sideDistX < dda->sideDistY)
		{
			dda->sideDistX += dda->deltaDistX;
			dda->mapX += dda->stepX;
			side = 0;
		}
		else
		{
			dda->sideDistY += dda->deltaDistY;
			dda->mapY += dda->stepY;
			side = 1;
		}
		if (mlx->config->map[dda->mapY]
			&& mlx->config->map[dda->mapY][dda->mapX] != '0')
			hit = true;
	}
	return (side);
}

int	send_rays(t_mlx *mlx, t_raycast *info)
{
	t_dda	dda;
	int		side;	
	int		wallHeight;

	side = apply_dda(mlx, info, &dda);
	if (side == 0)
		dda.perpWallDist = dda.sideDistX - dda.deltaDistX;
	else
		dda.perpWallDist = dda.sideDistY - dda.deltaDistY;
	wallHeight = (int)((double)HEIGHT / dda.perpWallDist);
	info->start = -wallHeight / 2 + HEIGHT / 2;
	if (info->start < 0)
		info->start = 0;
	info->end = wallHeight / 2 + HEIGHT / 2;
	if (info->end >= HEIGHT)
		info->end = HEIGHT - 1;
	return (side);
}

void	draw_line(t_mlx *mlx, t_raycast info, int line, int side)
{
	const int	x = line;
	int	y;
	int	color;

	y = 0;
	color = 0xff00ff;
	if (side == 1)
		color /= 4;
	while (y <= HEIGHT)
	{
		if (y < info.start)
			my_mlx_pixel_put(&(mlx->img), x, y, mlx->config->floor);
		else if (y >= info.start && y <= info.end)
			my_mlx_pixel_put(&(mlx->img), x, y, color);
		else if (y > info.end)
			my_mlx_pixel_put(&(mlx->img), x, y, mlx->config->ceiling);
		y++;
	}
}

void	raycasting(t_mlx *mlx)
{
	t_raycast	info;
	double		camera;
	int			side;
	int			i;

	init_raycast(mlx, &info);
	i = 0;
	while (i <= WIDTH)
	{
		camera = 2 * i / (double)WIDTH - 1;
		info.rayDirX = info.dirX + info.planeX * camera;
		info.rayDirY = info.dirY + info.planeY * camera;
		side = send_rays(mlx, &info);
		draw_line(mlx, info, i, side);
		i++;
	}
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img.img, 0, 0);
}
