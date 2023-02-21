/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:35:56 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/21 17:13:55 by adamiens         ###   ########.fr       */
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

	mlx.init = mlx_init();
	mlx.config = config;
	init_direction_vectors(&mlx);
	init_raycast(&mlx);
	if (mlx.init == NULL)
		free_render_exit(config, &mlx, "Initialisation error\n");
	mlx.win = mlx_new_window(mlx.init, WIDTH, HEIGHT, "Cub3D");
	if (mlx.win == NULL)
		free_render_exit(config, &mlx, "Initialisation error\n");
	mlx.img.img = mlx_new_image(mlx.init, WIDTH, HEIGHT);
	mlx.img.addr = mlx_get_data_addr
		(mlx.img.img, &(mlx.img.bits_per_px),
			&(mlx.img.line_len), &(mlx.img.endian));
	texture_to_tab(mlx.config, &mlx);
	raycasting(&mlx);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, &handle_key, &mlx);
	mlx_hook(mlx.win, DestroyNotify, StructureNotifyMask,
		&destroy_win, &mlx);
	mlx_loop(mlx.init);
}
