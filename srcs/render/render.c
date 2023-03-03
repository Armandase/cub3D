/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:35:56 by adamiens          #+#    #+#             */
/*   Updated: 2023/03/03 13:24:30 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"

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

void	init_frames(t_texture *config)
{
	config->frames[0] = ft_strdup("assets/frames_void/0.xpm");
	config->frames[1] = ft_strdup("assets/frames_void/1.xpm");
	config->frames[2] = ft_strdup("assets/frames_void/2.xpm");
	config->frames[3] = ft_strdup("assets/frames_void/3.xpm");
	config->frames[4] = ft_strdup("assets/frames_void/4.xpm");
	config->frames[5] = ft_strdup("assets/frames_void/5.xpm");
	config->frames[6] = ft_strdup("assets/frames_void/6.xpm");
	config->frames[7] = ft_strdup("assets/frames_void/7.xpm");
	config->frames[8] = ft_strdup("assets/frames_void/8.xpm");
	config->frames[9] = ft_strdup("assets/frames_void/9.xpm");
	config->frames[10] = ft_strdup("assets/frames_void/10.xpm");
	config->frames[11] = ft_strdup("assets/frames_void/11.xpm");
	config->frames[12] = ft_strdup("assets/frames_void/12.xpm");
	config->frames[13] = ft_strdup("assets/frames_void/13.xpm");
	config->frames[14] = ft_strdup("assets/frames_void/14.xpm");
	config->frames[15] = ft_strdup("assets/frames_void/15.xpm");
	config->frames[16] = ft_strdup("assets/frames_void/16.xpm");
	config->frames[17] = ft_strdup("assets/frames_void/17.xpm");
	config->frames[18] = ft_strdup("assets/frames_void/18.xpm");
	config->frames[19] = ft_strdup("assets/frames_void/19.xpm");
	config->frames[20] = ft_strdup("assets/frames_void/20.xpm");
	config->frames[21] = ft_strdup("assets/frames_void/21.xpm");
	config->frames[22] = ft_strdup("assets/frames_void/22.xpm");
}

void	render(t_texture *config)
{
	t_mlx	mlx;

	mlx.init = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	mlx.config = config;
	mlx.config->frame_id = 0;
	mlx_set_cursor_mode(mlx.init, MLX_MOUSE_HIDDEN);
	init_direction_vectors(&mlx);
	init_raycast(&mlx);
	if (mlx.init == NULL)
		free_render_exit(config, &mlx, "Initialisation error\n");
	mlx.img = mlx_new_image(mlx.init, WIDTH, HEIGHT);
	mlx_image_to_window(mlx.init, mlx.img, 0, 0);
	texture_to_tab(mlx.config, &mlx);
	raycasting(&mlx);
	mlx_loop_hook(mlx.init, handle_key, &mlx);
	mlx_loop(mlx.init);
}
