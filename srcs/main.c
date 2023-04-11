/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:44:19 by adamiens          #+#    #+#             */
/*   Updated: 2023/04/11 09:44:39 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parsing.h"
#include "../includes/render.h"

int	main(int ac, char **av)
{
	t_texture	config;

	config = init_texture();
	parsing(ac, av, &config);
	render(&config);
	return (0);
}
