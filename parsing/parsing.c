/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:28:53 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/12 10:27:42 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parsing(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		exit(1);
	}
	extension_check(av[1]);
	map_check(av[1]);
}
