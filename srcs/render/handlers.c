#include "../../includes/render.h"

void	free_img_tab(size_t **tab[4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 64)
		{
			free(tab[i][j]);
			j++;
		}
		free(tab[i]);
		i++;
	}
}

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
	free_img_tab(config->img_tab);
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

void	handle_key(void	*param)
{
	t_mlx	*mlx;
	double	tmp_dir_x;
	double	tmp_dir_y;
	double	tmp_plane_x;
	double	tmp_plane_y;

	mlx = param;
	tmp_dir_x = mlx->config->dir_x * MOVEMENT_SPEED;
	tmp_dir_y = mlx->config->dir_y * MOVEMENT_SPEED;
	tmp_plane_x = mlx->config->plane_x * MOVEMENT_SPEED;
	tmp_plane_y = mlx->config->plane_y * MOVEMENT_SPEED;
	if (mlx_is_key_down(mlx->init, MLX_KEY_ESCAPE))
	{
		mlx_terminate(mlx->init);
		free_texture(mlx->config);
		free(mlx->init);
	}
	if (mlx_is_key_down(mlx->init, MLX_KEY_W))
	{
		if (mlx->config->map[(int)mlx->config->pos_y]
			[(int)(mlx->config->pos_x + tmp_dir_x)] == '0')
			mlx->config->pos_x += tmp_dir_x;
		if (mlx->config->map[(int)(mlx->config->pos_y + tmp_dir_y)]
			[(int)mlx->config->pos_x] == '0')
			mlx->config->pos_y += tmp_dir_y;
	}
	if (mlx_is_key_down(mlx->init, MLX_KEY_S))
	{
		if (mlx->config->map[(int)mlx->config->pos_y]
			[(int)(mlx->config->pos_x - tmp_dir_x)] == '0')
			mlx->config->pos_x -= tmp_dir_x;
		if (mlx->config->map[(int)(mlx->config->pos_y - tmp_dir_y)]
			[(int)mlx->config->pos_x] == '0')
			mlx->config->pos_y -= tmp_dir_y;
	}
	if (mlx_is_key_down(mlx->init, MLX_KEY_D))
	{
		if (mlx->config->map[(int)mlx->config->pos_y]
			[(int)(mlx->config->pos_x + tmp_plane_x)] == '0')
			mlx->config->pos_x += tmp_plane_x;
		if (mlx->config->map[(int)(mlx->config->pos_y + tmp_plane_y)]
			[(int)mlx->config->pos_x] == '0')
			mlx->config->pos_y += tmp_plane_y;
	}
	if (mlx_is_key_down(mlx->init, MLX_KEY_A))
	{
		if (mlx->config->map[(int)mlx->config->pos_y]
			[(int)(mlx->config->pos_x - tmp_plane_x)] == '0')
			mlx->config->pos_x -= tmp_plane_x;
		if (mlx->config->map[(int)(mlx->config->pos_y - tmp_plane_y)]
			[(int)mlx->config->pos_x] == '0')
			mlx->config->pos_y -= tmp_plane_y;
	}
	if (mlx_is_key_down(mlx->init, MLX_KEY_LEFT))
		rotate_vectors(mlx, LEFT);
	if (mlx_is_key_down(mlx->init, MLX_KEY_RIGHT))
		rotate_vectors(mlx, RIGHT);
	mouse_hook_camera(mlx);
	raycasting(mlx);
}
