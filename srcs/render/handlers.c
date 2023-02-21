#include "../../includes/render.h"

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
	double			angle;
	const double	dir_x = mlx->config->dir_x;
	const double	dir_y = mlx->config->dir_y;
	const double	plane_x = mlx->config->plane_x;
	const double	plane_y = mlx->config->plane_y;

	angle = ROTATION_SPEED * (M_1_PI / 180.0);
	if (flag == LEFT)
		angle = -angle;
	mlx->config->dir_x = cos(angle) * dir_x - sin(angle) * dir_y;
	mlx->config->dir_y = sin(angle) * dir_x + cos(angle) * dir_y;
	mlx->config->plane_x = cos(angle) * plane_x - sin(angle) * plane_y;
	mlx->config->plane_y = sin(angle) * plane_x + cos(angle) * plane_y;
}

int	handle_key(int key, t_mlx *mlx)
{
	double	tmp_dir_x;
	double	tmp_dir_y;
	double	tmp_plane_x;
	double	tmp_plane_y;

	tmp_dir_x = mlx->config->dir_x * MOVEMENT_SPEED;
	tmp_dir_y = mlx->config->dir_y * MOVEMENT_SPEED;
	tmp_plane_x = mlx->config->plane_x * MOVEMENT_SPEED;
	tmp_plane_y = mlx->config->plane_y * MOVEMENT_SPEED;
	if (key == XK_Escape)
		destroy_win(mlx);
	if (key == 'a' || key == 'd' || key == 'w' || key == 's'
		|| key == XK_Left || key == XK_Right)
	{
		if (key == 'w')
		{
			if (mlx->config->map[(int)mlx->config->pos_y]
				[(int)(mlx->config->pos_x + tmp_dir_x)] == '0')
				mlx->config->pos_x += tmp_dir_x;
			if (mlx->config->map[(int)(mlx->config->pos_y + tmp_dir_y)]
				[(int)mlx->config->pos_x] == '0')
				mlx->config->pos_y += tmp_dir_y;
		}
		if (key == 's')
		{
			if (mlx->config->map[(int)mlx->config->pos_y]
				[(int)(mlx->config->pos_x - tmp_dir_x)] == '0')
				mlx->config->pos_x -= tmp_dir_x;
			if (mlx->config->map[(int)(mlx->config->pos_y - tmp_dir_y)]
				[(int)mlx->config->pos_x] == '0')
				mlx->config->pos_y -= tmp_dir_y;
		}
		if (key == 'd')
		{
			if (mlx->config->map[(int)mlx->config->pos_y]
				[(int)(mlx->config->pos_x + tmp_plane_x)] == '0')
				mlx->config->pos_x += tmp_plane_x;
			if (mlx->config->map[(int)(mlx->config->pos_y + tmp_plane_y)]
				[(int)mlx->config->pos_x] == '0')
				mlx->config->pos_y += tmp_plane_y;
		}
		if (key == 'a')
		{
			if (mlx->config->map[(int)mlx->config->pos_y]
				[(int)(mlx->config->pos_x - tmp_plane_x)] == '0')
				mlx->config->pos_x -= tmp_plane_x;
			if (mlx->config->map[(int)(mlx->config->pos_y - tmp_plane_y)]
				[(int)mlx->config->pos_x] == '0')
				mlx->config->pos_y -= tmp_plane_y;
		}
		if (key == XK_Left)
			rotate_vectors(mlx, LEFT);
		if (key == XK_Right)
			rotate_vectors(mlx, RIGHT);
		raycasting(mlx);
	}
	return (0);
}
