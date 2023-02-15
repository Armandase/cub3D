/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:01:52 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/15 14:16:26 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	verif_top_bot(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' || line[i] != ' ')
			return (1);
		i++;
	}
	if (ft_strlen(&line[i]) > 1)
		return (1);
	return (0);
}

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
	return (strs);
}

void	get_map(t_texture *config, char *buf, t_map *map, int fd)
{
	map->map = copy_map(fd, buf);
	//if (verif_top_bot(buf, map))
	//	free_texture_exit(*config, buf);
	for(int	i = 0; map->map[i]; i++)
		ft_printf("%s\n", map->map[i]);
	(void)config;
	ft_free_strs(map->map);
	free_texture_exit(config, char *buf);
}
