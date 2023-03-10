/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:14:22 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/21 17:14:23 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"

void	swap_axes(size_t ***array)
{
	int		x;
	int		y;
	size_t	tmp;

	x = 0;
	while (x < 64)
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

void	copy_texture_from_img_to_array(t_texture *config, t_data *img, int i)
{
	int		x;
	int		y;

	x = 0;
	config->img_tab[i] = malloc(sizeof(size_t *) * 64);
	while (x < 64)
	{
		y = 0;
		config->img_tab[i][x] = malloc(sizeof(size_t) * 64);
		while (y < 64)
		{
			config->img_tab[i][x][y] = get_color_from_img(img, x, y);
			y = y + 1;
		}
		x = x + 1;
	}
	swap_axes(&config->img_tab[i]);
}

void	texture_to_tab(t_texture *config, t_mlx *mlx)
{
	int		i;
	int		img_len_x;
	int		img_len_y;
	t_data	img;

	i = 0;
	while (i < 4)
	{
		if (i == 0)
			img.img = mlx_xpm_file_to_image
				(mlx->init, config->no, &img_len_x, &img_len_y);
		else if (i == 1)
			img.img = mlx_xpm_file_to_image
				(mlx->init, config->so, &img_len_x, &img_len_y);
		else if (i == 2)
			img.img = mlx_xpm_file_to_image
				(mlx->init, config->ea, &img_len_x, &img_len_y);
		else if (i == 3)
			img.img = mlx_xpm_file_to_image
				(mlx->init, config->we, &img_len_x, &img_len_y);
		img.addr = mlx_get_data_addr (img.img, &img.bits_per_px,
				&img.line_len, &img.endian);
		copy_texture_from_img_to_array(config, &img, i);
		i++;
	}
}
