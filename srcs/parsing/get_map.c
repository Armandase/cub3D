/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:01:52 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/17 16:52:29 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	**add_strs_back(char *to_add, char	**strs)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_strlen_2d((const char **)strs) + 2));
	while (strs[i])
	{
		ret[i] = ft_strdup(strs[i]);
		i++;
	}
	ret[i] = ft_strdup(to_add);
	ret[i + 1] = NULL;
	ft_free_strs(strs);
	ft_free((void *)&to_add);
	return (ret);
}

char	**copy_map(int fd, char *first_line)
{
	char	**strs;
	char	*to_add;

	strs = malloc(sizeof(char *) * 1);
	strs[0] = NULL;
	strs = add_strs_back(first_line, strs);
	while (1)
	{
		to_add = get_next_line(fd);
		if (to_add == NULL)
			break ;
		strs = add_strs_back(to_add, strs);
	}
	close(fd);
	return (strs);
}

void	get_map(t_texture *config, char *buf, int fd)
{
	config->map = copy_map(fd, buf);
	if (verif_map(config) == false)
		print_error_exit("Invalid map\n");
	ft_free_strs(config->map);
	(void)config;
	//free_texture_exit(*config, NULL);
}
