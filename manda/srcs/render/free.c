/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:56:45 by ulayus            #+#    #+#             */
/*   Updated: 2023/04/12 10:56:48 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"

static void	free_img_tab(u_int32_t **tab, int len)
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
