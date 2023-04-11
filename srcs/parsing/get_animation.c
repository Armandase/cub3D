/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 10:26:16 by adamiens          #+#    #+#             */
/*   Updated: 2023/04/11 14:40:39 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include "../../includes/render.h"

void	img_open_error(t_mlx *mlx, char *error)
{
	free_all(mlx->config);
	mlx_delete_image(mlx->init, mlx->img);
	mlx_terminate(mlx->init);
	print_error_exit(error);
}

void	fill_img_array(char *path, t_texture *config, t_mlx *mlx, int i)
{
	int			fd;
	mlx_image_t	*img;
	xpm_t		*xpm;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		img_open_error(mlx, "open error\n");
	else
		close(fd);
	xpm = mlx_load_xpm42(path);
	if (!xpm)
		img_open_error(mlx, "XPM open error\n");
	img = mlx_texture_to_image(mlx->init, &xpm->texture);
	if (!img)
		img_open_error(mlx, "XPM error\n");
	copy_texture_from_img_to_array(img, &config->img_anim[i], mlx, 128);
	mlx_delete_texture(&xpm->texture);
}

void	get_hourglass(char *path, t_texture *config, t_mlx *mlx, int i)
{
	int			fd;
	mlx_image_t	*img;
	xpm_t		*xpm;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		img_open_error(mlx, "open error\n");
	else
		close(fd);
	xpm = mlx_load_xpm42(path);
	if (!xpm)
		img_open_error(mlx, "XPM open error\n");
	img = mlx_texture_to_image(mlx->init, &xpm->texture);
	if (!img)
		img_open_error(mlx, "XPM error\n");
	copy_texture_from_img_to_array(img, &config->hourglass[i], mlx, 512);
	mlx_delete_texture(&xpm->texture);
}

void	get_animation(t_texture *config, t_mlx *mlx)
{
	config->img_door = NULL;
	config->hourglass[0] = NULL;
	config->hourglass[1] = NULL;
	config->hourglass[2] = NULL;
	config->hourglass[3] = NULL;
	config->hourglass[4] = NULL;
	config->img_tab[0] = NULL;
	config->img_tab[1] = NULL;
	config->img_tab[2] = NULL;
	config->img_tab[3] = NULL;
	config->img_anim[0] = NULL;
	config->img_anim[1] = NULL;
	config->img_anim[2] = NULL;
	fill_img_array("./assets/fck00.xpm42", config, mlx, 0);
	fill_img_array("./assets/fck01.xpm42", config, mlx, 1);
	fill_img_array("./assets/fck02.xpm42", config, mlx, 2);
	get_hourglass("./assets/hourglass0.xpm42", config, mlx, 0);
	get_hourglass("./assets/hourglass1.xpm42", config, mlx, 1);
	get_hourglass("./assets/hourglass2.xpm42", config, mlx, 2);
	get_hourglass("./assets/hourglass3.xpm42", config, mlx, 3);
	get_hourglass("./assets/hourglass4.xpm42", config, mlx, 4);
	config->anim = 0;
}
