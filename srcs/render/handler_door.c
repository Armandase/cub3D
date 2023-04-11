/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:59:02 by ulayus            #+#    #+#             */
/*   Updated: 2023/04/11 14:59:27 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"

static void	*routine(void *data)
{
	t_texture	*config;

	config = (t_texture *)data;
	sleep(2);
	pthread_mutex_lock(&config->door_opened_mtx);
	if (config->door_opened == false)
		config->door_opened = true;
	else
		config->door_opened = false;
	pthread_mutex_unlock(&config->door_opened_mtx);
	return (NULL);
}

void	handle_key_released(mlx_key_data_t keydata, void *param)
{
	t_mlx			*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_RELEASE)
	{
		system("paplay assets/biden_blast.ogg &");
		pthread_create(&mlx->config->pthread, NULL, &routine, mlx->config);
		pthread_detach(mlx->config->pthread);
	}
}
