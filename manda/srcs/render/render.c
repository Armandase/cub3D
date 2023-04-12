/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:13:04 by adamiens          #+#    #+#             */
/*   Updated: 2023/04/12 13:37:31 by ulayus           ###   ########.fr       */
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

static void	ft_exit(t_mlx *mlx)
{
	mlx_terminate(mlx->init);
	free_all(mlx->config);
	exit(0);
}

void	render(t_texture *config)
{
	t_mlx	mlx;

	mlx.init = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (mlx.init == NULL)
		free_render_exit(config, &mlx, "Initialisation error\n");
	set_icon(&mlx, config);
	mlx.config = config;
	init_direction_vectors(&mlx);
	init_raycast(&mlx);
	if (mlx.init == NULL)
		free_render_exit(config, &mlx, "Initialisation error\n");
	mlx.img = mlx_new_image(mlx.init, WIDTH, HEIGHT);
	if (mlx.img == NULL)
		free_render_exit(config, &mlx, "Image error\n");
	mlx_image_to_window(mlx.init, mlx.img, 0, 0);
	if (texture_to_tab(mlx.config, &mlx) == NULL)
		ft_exit(&mlx);
	raycasting(&mlx);
	mlx_loop_hook(mlx.init, handle_key, &mlx);
	mlx_loop(mlx.init);
	ft_exit(&mlx);
}
