/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:30:11 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/15 09:39:21 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	print_error_exit(char *error)
{
	ft_putstr_fd(error, 2);
	exit(1);
}

void	extension_check(char *av)
{
	char	*extend;

	if (ft_strlen(av) < ft_strlen(".cub"))
		print_error_exit("Wrong number of arguments\n");
	extend = ft_strnstr(av, ".cub", ft_strlen(av));
	if (!extend || ft_strlen(extend) > ft_strlen(".cub"))
		print_error_exit("Wrong number of arguments\n");
}
