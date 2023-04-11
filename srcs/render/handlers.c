#include "../../includes/render.h"

void	free_img_tab(u_int32_t **tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_texture(t_texture *config)
{
	int	i;

	ft_free((void *)&config->no);
	ft_free((void *)&config->so);
	ft_free((void *)&config->we);
	ft_free((void *)&config->ea);
	ft_free_strs(config->map);
	i = 0;
	while (i < 4)
	{
		if (config->img_tab[i])
			free_img_tab(config->img_tab[i], 64);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (config->img_anim[i])
			free_img_tab(config->img_anim[i], 128);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		if (config->hourglass[i])
			free_img_tab(config->hourglass[i], 512);
		i++;
	}
	if (config->img_door)
		free_img_tab(config->img_door, 64);
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

bool	check_cell(char cell, t_texture *config)
{
	if (cell == '0' || cell == config->orientation || cell == 'd')
		return (true);
	return (false);
}

void	*routine(void *data)
{
	t_texture	*config;

	config = (t_texture *)data;
	sleep(2);
	pthread_mutex_lock(&config->door_opened_mtx);	
	if (config->door_opened == false)
		config->door_opened = true;
	else
		config->door_opened = false;
	pthread_mutex_unlock(&config->door_opened_mtx);	
	return (NULL);
}

void	handle_key_released(mlx_key_data_t keydata, void *param)
{
	t_mlx			*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_RELEASE)
	{
		system("paplay assets/biden_blast.ogg &"); 
		pthread_create(&mlx->config->pthread, NULL, &routine, mlx->config);
		pthread_detach(mlx->config->pthread);
	}
}

void	handle_key(void *param)
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
		mlx_delete_image(mlx->init, mlx->img);
		mlx_terminate(mlx->init);
		free_texture(mlx->config);
		exit(0);
	}
	if (mlx_is_key_down(mlx->init, MLX_KEY_W))
	{
		if (check_cell(mlx->config->map[(int)mlx->config->pos_y]
			[(int)(mlx->config->pos_x + tmp_dir_x)], mlx->config) == true)
			mlx->config->pos_x += tmp_dir_x;
		if (check_cell(mlx->config->map[(int)(mlx->config->pos_y + tmp_dir_y)]
			[(int)mlx->config->pos_x], mlx->config) == true)
			mlx->config->pos_y += tmp_dir_y;
	}
	if (mlx_is_key_down(mlx->init, MLX_KEY_S))
	{
		if (check_cell(mlx->config->map[(int)mlx->config->pos_y]
			[(int)(mlx->config->pos_x - tmp_dir_x)], mlx->config) == true)
			mlx->config->pos_x -= tmp_dir_x;
		if (check_cell(mlx->config->map[(int)(mlx->config->pos_y - tmp_dir_y)]
			[(int)mlx->config->pos_x], mlx->config) == true)
			mlx->config->pos_y -= tmp_dir_y;
	}
	if (mlx_is_key_down(mlx->init, MLX_KEY_D))
	{
		if (check_cell(mlx->config->map[(int)mlx->config->pos_y]
			[(int)(mlx->config->pos_x + tmp_plane_x)], mlx->config) == true)
			mlx->config->pos_x += tmp_plane_x;
		if (check_cell(mlx->config->map[(int)(mlx->config->pos_y + tmp_plane_y)]
			[(int)mlx->config->pos_x], mlx->config) == true)
			mlx->config->pos_y += tmp_plane_y;
	}
	if (mlx_is_key_down(mlx->init, MLX_KEY_A))
	{
		if (check_cell(mlx->config->map[(int)mlx->config->pos_y]
			[(int)(mlx->config->pos_x - tmp_plane_x)], mlx->config) == true)
			mlx->config->pos_x -= tmp_plane_x;
		if (check_cell(mlx->config->map[(int)(mlx->config->pos_y - tmp_plane_y)]
			[(int)mlx->config->pos_x], mlx->config) == true)
			mlx->config->pos_y -= tmp_plane_y;
	}
	if (mlx_is_key_down(mlx->init, MLX_KEY_LEFT))
		rotate_vectors(mlx, LEFT);
	if (mlx_is_key_down(mlx->init, MLX_KEY_RIGHT))
		rotate_vectors(mlx, RIGHT);
	if (mlx_is_key_down(mlx->init, MLX_KEY_SPACE))
	{
		mlx->config->anim = 1;
		system("paplay assets/biden_su.ogg &"); 
	}
	mouse_hook_camera(mlx);
	raycasting(mlx);
}
