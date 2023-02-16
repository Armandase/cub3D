/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:35:56 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/16 13:57:17 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	free_render_exit(t_texture *config, t_mlx *mlx, char *error)
{
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
void	render(t_texture *config)
{
	t_mlx	mlx;

	mlx.init = mlx_init();
	if (mlx.init == NULL)
		free_render_exit(config, &mlx, "Initialisation error\n");
	mlx.win = mlx_new_window
		(mlx.init, WIDTH, HEIGHT, "Cub3D");
	if (mlx.win == NULL)
		free_render_exit(config, &mlx, "Initialisation error\n");
	mlx.img = mlx_new_image(mlx.init, WIDTH, HEIGHT);
	mlx.img_addr = mlx_get_data_addr
		(mlx.img, &(mlx.bits_per_px),
			&(mlx.line_len), &(mlx.endian));
}