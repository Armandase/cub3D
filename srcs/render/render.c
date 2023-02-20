/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:35:56 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/20 13:23:45 by adamiens         ###   ########.fr       */
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
	mlx->config->posX = mlx->config->y;
	mlx->config->posY = mlx->config->x;
	mlx->config->dirX = 0;
	mlx->config->dirY = 0;
	if (mlx->config->orientation == 'N')
		mlx->config->dirY = -1;
	else if (mlx->config->orientation == 'S')
		mlx->config->dirY = 1;
	else if (mlx->config->orientation == 'E')
		mlx->config->dirX = 1;
	else if (mlx->config->orientation == 'W')
		mlx->config->dirX = -1;
}

void	init_raycast(t_mlx *mlx)
{
	double	dirX;
	double	dirY;

	dirX = 0;
	dirY = 0;
	if (mlx->config->orientation == 'N')
		dirY = -1;
	else if (mlx->config->orientation == 'S')
		dirY = 1;
	else if (mlx->config->orientation == 'E')
		dirX = 1;
	else if (mlx->config->orientation == 'W')
		dirX = -1;
	mlx->config->planeX = -(dirY) * 0.66;
	mlx->config->planeY = dirX * 0.66;
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
	raycasting(&mlx);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, &handle_key, &mlx);
	mlx_hook(mlx.win, DestroyNotify, StructureNotifyMask,
		  &destroy_win, &mlx);
	mlx_loop(mlx.init);
}
