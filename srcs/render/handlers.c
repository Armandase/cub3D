# include "../../includes/render.h"

static void	free_texture(t_texture *config)
{
	if (config->no != NULL)
		ft_free((void *)&config->no);
	if (config->so != NULL)
		ft_free((void *)&config->so);
	if (config->we != NULL)
		ft_free((void *)&config->we);
	if (config->ea != NULL)
		ft_free((void *)&config->ea);
	ft_free_strs(config->map);
}

int	destroy_win(t_mlx *mlx)
{
	mlx_loop_end(mlx->init);
	mlx_destroy_image(mlx->init, mlx->img.img);
	mlx_clear_window(mlx->init, mlx->win);
	mlx_destroy_window(mlx->init, mlx->win);
	mlx_destroy_display(mlx->init);
	free_texture(mlx->config);
	free(mlx->init);
	exit (0);
	return (0);
}

void	rotate_vectors(t_mlx *mlx, int flag)
{
	double	angle;
	const double	dirX = mlx->config->dirX;
	const double	dirY = mlx->config->dirY;
	const double	planeX = mlx->config->planeX;
	const double	planeY = mlx->config->planeY;

	angle = ROTATION_SPEED * (M_1_PI / 180.0);
	if (flag == LEFT)
		angle = -angle;
	mlx->config->dirX = cos(angle) * dirX - sin(angle) * dirY;
	mlx->config->dirY = sin(angle) * dirX + cos(angle) * dirY;
	mlx->config->planeX = cos(angle) * planeX - sin(angle) * planeY;
	mlx->config->planeY = sin(angle) * planeX + cos(angle) * planeY;
}

int	handle_key(int key, t_mlx *mlx)
{
	double	tmp_dirX;
	double	tmp_dirY;
	double	tmp_planeX;
	double	tmp_planeY;

	tmp_dirX = mlx->config->dirX * MOVEMENT_SPEED;
	tmp_dirY = mlx->config->dirY * MOVEMENT_SPEED;
	tmp_planeX = mlx->config->planeX * MOVEMENT_SPEED;
	tmp_planeY = mlx->config->planeY * MOVEMENT_SPEED;
	if (key == XK_Escape)
		destroy_win(mlx);
	if (key == 'a' || key == 'd' || key == 'w' || key == 's'
		|| key == XK_Left || key == XK_Right)
	{
		if (key == 'w')
		{
			if (mlx->config->map[(int)mlx->config->posY][(int)(mlx->config->posX + tmp_dirX)] == '0')
				mlx->config->posX += tmp_dirX;
			if (mlx->config->map[(int)(mlx->config->posY + tmp_dirY)][(int)mlx->config->posX] == '0')
				mlx->config->posY += tmp_dirY;
		}
		if (key == 's')
		{
			if (mlx->config->map[(int)mlx->config->posY][(int)(mlx->config->posX - tmp_dirX)] == '0')
				mlx->config->posX -= tmp_dirX;
			if (mlx->config->map[(int)(mlx->config->posY - tmp_dirY)][(int)mlx->config->posX] == '0')
				mlx->config->posY -= tmp_dirY;
		}
		if (key == 'a')
		{
			if (mlx->config->map[(int)mlx->config->planeY][(int)(mlx->config->planeX - tmp_dirX)] == '0')
				mlx->config->planeX -= tmp_dirX;
			if (mlx->config->map[(int)(mlx->config->planeY - tmp_dirY)][(int)mlx->config->planeX] == '0')
				mlx->config->planeY -= tmp_dirY;
		}
		if (key == 'd')
		{
			if (mlx->config->map[(int)mlx->config->planeY][(int)(mlx->config->planeX - tmp_dirX)] == '0')
				mlx->config->planeX -= tmp_dirX;
			if (mlx->config->map[(int)(mlx->config->planeY - tmp_dirY)][(int)mlx->config->planeX] == '0')
				mlx->config->planeY -= tmp_dirY;
		}
		if (key == XK_Left)
			rotate_vectors(mlx, LEFT);
		if (key == XK_Right)
			rotate_vectors(mlx, RIGHT);
		raycasting(mlx);
	}
	return (0);
}
