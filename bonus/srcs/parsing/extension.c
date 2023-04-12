/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:30:11 by adamiens          #+#    #+#             */
/*   Updated: 2023/04/12 13:15:20 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	check_add(char **strs, char *to_add, int fd)
{
	if (ft_strcmp(to_add, "\n") == 0)
	{
		close (fd);
		ft_free_strs(strs);
		free(to_add);
		return (1);
	}
	return (0);
}

void	print_error_exit(char *error)
{
	ft_putstr_fd("Error\n", 2);
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

void	verif_path_texture(t_texture *config)
{
	int	fd;

	fd = open(config->no, O_RDONLY);
	if (fd < 0)
		free_strs_texture_exit(config, "Open error\n");
	else
		close(fd);
	fd = open(config->so, O_RDONLY);
	if (fd < 0)
		free_strs_texture_exit(config, "Open error\n");
	else
		close(fd);
	fd = open(config->we, O_RDONLY);
	if (fd < 0)
		free_strs_texture_exit(config, "Open error\n");
	else
		close(fd);
	fd = open(config->ea, O_RDONLY);
	if (fd < 0)
		free_strs_texture_exit(config, "Open error\n");
	else
		close(fd);
}
