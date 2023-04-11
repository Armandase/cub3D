/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:28:53 by adamiens          #+#    #+#             */
/*   Updated: 2023/04/11 10:48:30 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	map_check(char	*av, t_texture *config)
{
	int			fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		print_error_exit("Open error\n");
	configuration(fd, config);
	verif_path_texture(config);
}

void	parsing(int ac, char **av, t_texture *config)
{
	if (ac != 2)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		exit(1);
	}
	extension_check(av[1]);
	map_check(av[1], config);
}
