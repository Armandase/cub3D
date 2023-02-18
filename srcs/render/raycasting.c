# include "../../includes/render.h"

# define PLANE_X 0
# define PLANE_Y 0.66

void	init_raycast(t_mlx *mlx, t_raycast *info)
{
	info->posX = mlx->x;
	info->posY = mlx->y;
	info->dirX = 0;
	info->dirY = 0;
	if (mlx->orientation == NORTH)
		info->dirY = 1;
	else if (mlx->orientation == SOUTH)
		info->dirY = -1;
	else if (mlx->orientation == WEST)
		info->dirX = -1;
	else if (mlx->orientation == EAST)
		info->dirX = 1;
}

void	init_dda(t_dda *dda, t_raycast *info)
{
	dda->mapX = (int)(info->posX);
	dda->mapY = (int)(info->posY);
	if (info->rayDirX == 0)
		dda->deltaDistX = 1e30;
	else
		dda->deltaDistX = sqrt(1 + pow(info->rayDirY, 2.0) / pow(info->rayDirX, 2.0));
	if (info->rayDirY == 0)
		dda->deltaDistY = 1e30;
	else
		dda->deltaDistY = sqrt(1 + pow(info->rayDirX, 2.0) / pow(info->rayDirY, 2.0));
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

void	send_rays(t_mlx *mlx, t_raycast *info)
{
	t_dda	dda;
	int		side;	
	int		wallHeight;

	side = apply_dda(mlx, info, &dda);
	if (side == 0)
		dda.perpWallDist = dda.sideDistX - dda.deltaDistX;
	else
		dda.perpWallDist = dda.sideDistY - dda.deltaDistY;
	wallHeight = (int)(HEIGHT / dda.perpWallDist);
	info->start = -wallHeight / 2 + HEIGHT / 2;
	if (info->start < 0)
		info->start = 0;
	info->end = wallHeight / 2 + HEIGHT / 2;
	if (info->end >= HEIGHT)
		info->end = HEIGHT - 1;
}

void	draw_line(t_mlx *mlx, t_raycast info, int line)
{
	(void)mlx;
	printf("Start of line %d: %d\n", line, info.start);
	printf("End of line %d: %d\n", line, info.end);
}

void	raycasting(t_mlx *mlx)
{
	t_raycast	info;
	double		camera;
	int			i;

	i = 0;
	init_raycast(mlx, &info);
	while (i < WIDTH)
	{
		camera = 2 * i / (double)WIDTH - 1;
		info.rayDirX = info.dirX + PLANE_X * camera;
		info.rayDirY = info.dirY + PLANE_Y * camera;
		send_rays(mlx, &info);
		draw_line(mlx, info, i);
		usleep(500);
		i++;
	}
}
