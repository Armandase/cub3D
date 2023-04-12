/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:26:07 by adamiens          #+#    #+#             */
/*   Updated: 2023/04/12 10:31:23 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"

void	swap_axes(u_int32_t ***array, int max)
{
	int			x;
	int			y;
	uint32_t	tmp;

	x = 0;
	while (x < max)
	{
		y = 0;
		while (y < x)
		{
			tmp = (*array)[x][y];
			(*array)[x][y] = (*array)[y][x];
			(*array)[y][x] = tmp;
			y++;
		}
		x++;
	}
}

void	copy_texture_from_img_to_array(mlx_image_t *img,
		uint32_t ***img_tab, t_mlx *mlx, int max)
{
	int		x;
	int		y;

	x = 0;
	(*img_tab) = malloc(sizeof(uint32_t *) * max);
	if (!*img_tab)
		free_render_exit(mlx->config, mlx, "Malloc error\n");
	while (x < max)
	{
		y = 0;
		(*img_tab)[x] = malloc(sizeof(uint32_t) * max);
		if (!(*img_tab)[x])
			free_render_exit(mlx->config, mlx, "Malloc error\n");
		while (y < max)
		{
			(*img_tab)[x][y] = get_color_from_img(img, x, y);
			y = y + 1;
		}
		x = x + 1;
	}
	swap_axes(img_tab, max);
	if (img)
		mlx_delete_image(mlx->init, img);
}

void	texture_to_tab(t_texture *config, t_mlx *mlx)
{
	int			i;
	mlx_image_t	*img;
	xpm_t		*xpm;

	i = 0;
	while (i < 4)
	{
		if (i == 0)
			xpm = mlx_load_xpm42(config->no);
		else if (i == 1)
			xpm = mlx_load_xpm42(config->so);
		else if (i == 2)
			xpm = mlx_load_xpm42(config->ea);
		else if (i == 3)
			xpm = mlx_load_xpm42(config->we);
		img = mlx_texture_to_image(mlx->init, &xpm->texture);
		copy_texture_from_img_to_array(img, &config->img_tab[i], mlx, 64);
		mlx_delete_texture(&xpm->texture);
		i++;
	}
}
