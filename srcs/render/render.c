#include "../../includes/render.h"
#include <stdio.h>

void	free_render_exit(t_texture *config, t_mlx *mlx, char *error)
{
	(void)mlx;
	if (config->no != NULL)
		ft_free((void *)&config->no);
	if (config->so != NULL)
		ft_free((void *)&config->so);
	if (config->we != NULL)
		ft_free((void *)&config->we);
	if (config->ea != NULL)
		ft_free((void *)&config->ea);
	print_error_exit(error);
}

void	init_direction_vectors(t_mlx *mlx)
{
	mlx->config->pos_x = mlx->config->y;
	mlx->config->pos_y = mlx->config->x;
	mlx->config->dir_x = 0;
	mlx->config->dir_y = 0;
	if (mlx->config->orientation == 'N')
		mlx->config->dir_y = -1;
	else if (mlx->config->orientation == 'S')
		mlx->config->dir_y = 1;
	else if (mlx->config->orientation == 'E')
		mlx->config->dir_x = 1;
	else if (mlx->config->orientation == 'W')
		mlx->config->dir_x = -1;
}

void	mouse_hook_camera(void *data)
{
	t_mlx		*mlx;
	static int	x;
	int			y;
	int			before;

	mlx = (t_mlx *)data;
	y = 0;
	before = x;
	mlx_get_mouse_pos(mlx->init, &x, &y);
	if (x == before)
		return ;
	if (x > before)
		rotate_vectors(mlx, RIGHT);
	if (x < before)
		rotate_vectors(mlx, LEFT);
	mlx_set_mouse_pos(mlx->init, WIDTH / 2, HEIGHT / 2);
	mlx_get_mouse_pos(mlx->init, &x, &y);
}

void	init_raycast(t_mlx *mlx)
{
	double	dir_x;
	double	dir_y;

	dir_x = 0;
	dir_y = 0;
	if (mlx->config->orientation == 'N')
		dir_y = -1;
	else if (mlx->config->orientation == 'S')
		dir_y = 1;
	else if (mlx->config->orientation == 'E')
		dir_x = 1;
	else if (mlx->config->orientation == 'W')
		dir_x = -1;
	mlx->config->plane_x = -(dir_y) * 0.66;
	mlx->config->plane_y = dir_x * 0.66;
}

void	render(t_texture *config)
{
	t_mlx	mlx;

	mlx.init = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (mlx.init == NULL)
		free_render_exit(config, &mlx, "Initialisation error\n");
	mlx.icon = mlx_load_xpm42(config->so);
	if (mlx.icon == NULL)
		free_render_exit(config, &mlx, "Icon error\n");
	mlx_set_icon(mlx.init, &mlx.icon->texture);
	mlx_delete_xpm42(mlx.icon);
	mlx.config = config;
	get_animation(config, &mlx);
	mlx_set_cursor_mode(mlx.init, MLX_MOUSE_HIDDEN);
	init_direction_vectors(&mlx);
	init_raycast(&mlx);
	if (mlx.init == NULL)
		free_render_exit(config, &mlx, "Initialisation error\n");
	mlx.img = mlx_new_image(mlx.init, WIDTH, HEIGHT);
	if (mlx.img == NULL)
		free_render_exit(config, &mlx, "Image error\n");
	mlx_image_to_window(mlx.init, mlx.img, 0, 0);
	texture_to_tab(mlx.config, &mlx);
	raycasting(&mlx);
	mlx_key_hook(mlx.init, &handle_key_released, &mlx);
	mlx_loop_hook(mlx.init, handle_key, &mlx);
	mlx_loop(mlx.init);
}
