/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:55:04 by ulayus            #+#    #+#             */
/*   Updated: 2023/04/11 14:55:24 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"

void	free_img_tab(u_int32_t **tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	free_texture(t_texture *config)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (config->img_tab[i])
			free_img_tab(config->img_tab[i], 64);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (config->img_anim[i])
			free_img_tab(config->img_anim[i], 128);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		if (config->hourglass[i])
			free_img_tab(config->hourglass[i], 512);
		i++;
	}
	if (config->img_door)
		free_img_tab(config->img_door, 64);
}

void	free_all(t_texture *config)
{
	ft_free((void *)&config->no);
	ft_free((void *)&config->so);
	ft_free((void *)&config->we);
	ft_free((void *)&config->ea);
	ft_free_strs(config->map);
	free_texture(config);
}
