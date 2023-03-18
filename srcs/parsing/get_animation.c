/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:26:16 by adamiens          #+#    #+#             */
/*   Updated: 2023/03/18 13:29:39 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	fill_img_array(char *path, t_texture *config, t_mlx *mlx, int i)
{
	int			fd;
	mlx_image_t	*img;
	xpm_t		*xpm;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		free_strs_texture_exit(config, "Open error\n");
	xpm = mlx_load_xpm42(path);
	if (!xpm)
		free_strs_texture_exit(config, "XPM open error\n");
	img = mlx_texture_to_image(mlx->init, &xpm->texture);
	if (!img)
		free_strs_texture_exit(config, "XPM error\n");
	copy_texture_from_img_to_array(img, &config->img_anim[i], mlx, 128);
	mlx_delete_texture(&xpm->texture);
}

void	get_animation(t_texture *config, t_mlx *mlx)
{
	fill_img_array("./assets/fck00.xpm42", config, mlx, 0);
	fill_img_array("./assets/fck01.xpm42", config, mlx, 1);
	fill_img_array("./assets/fck02.xpm42", config, mlx, 2);
}
