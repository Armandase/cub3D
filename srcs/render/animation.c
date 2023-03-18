/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 11:12:14 by adamiens          #+#    #+#             */
/*   Updated: 2023/03/18 14:35:07 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"

void	render_animation(t_mlx *mlx, int img)
{
	int	i;
	int	j;
	int	scale;
	int	offset;

	scale = 256;
	offset = scale / 128;
	i = WIDTH - scale;
	while (i < WIDTH)
	{
		j = HEIGHT - scale;
		while (j < HEIGHT)
		{
			if (mlx->config->img_anim[img][(i - WIDTH + scale) / offset]
				[(j - HEIGHT + scale) / offset] >> 24)
				mlx_put_pixel(mlx->img, i, j, mlx->config->img_anim[img]
				[(i - WIDTH + scale) / offset][(j - HEIGHT + scale) / offset]);
			j++;
		}
		i++;
	}
}

void	anim(t_mlx *mlx)
{
	static double	time;
	static int		i;

	if (mlx_get_time() - time > 0.2)
	{
		time = mlx_get_time();
		i++;
		if (i == 3)
			i = 0;
	}
	render_animation(mlx, i);
}
