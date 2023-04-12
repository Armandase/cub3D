/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:01:52 by adamiens          #+#    #+#             */
/*   Updated: 2023/04/11 10:52:46 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	**add_strs_back(char *to_add, char	**strs)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_strlen_2d((const char **)strs) + 2));
	if (!ret)
		return (NULL);
	while (strs[i])
	{
		ret[i] = ft_strdup(strs[i]);
		if (!ret[i])
		{
			ft_free_strs(strs);
			return (NULL);
		}
		i++;
	}
	ret[i] = ft_strdup(to_add);
	if (!ret[i])
		return (NULL);
	ret[i + 1] = NULL;
	ft_free_strs(strs);
	ft_free((void *)&to_add);
	return (ret);
}

void	set_spawn(t_texture *config, int i, int j, int *finded)
{
	if (config->map[i][j] == 'N')
	{
		config->orientation = 'N';
		config->x = i;
		config->y = j;
	}
	else if (config->map[i][j] == 'S')
	{
		config->orientation = 'S';
		config->x = i;
		config->y = j;
	}
	else if (config->map[i][j] == 'E')
	{
		config->orientation = 'E';
		config->x = i;
		config->y = j;
	}
	else if (config->map[i][j] == 'W')
	{
		config->orientation = 'W';
		config->x = i;
		config->y = j;
	}
	*finded = 1;
}

void	find_spawn(t_texture *config)
{
	int	i;
	int	j;
	int	finded;

	i = 0;
	finded = false;
	while (config->map[i])
	{
		j = 0;
		while (config->map[i][j])
		{
			if ((config->map[i][j] == 'N' || config->map[i][j] == 'S'
				|| config->map[i][j] == 'E' || config->map[i][j] == 'W')
					&& finded)
			{
				ft_free_strs(config->map);
				free_texture_exit(*config, NULL, 0);
			}
			else if (config->map[i][j] == 'N' || config->map[i][j] == 'S'
				|| config->map[i][j] == 'E' || config->map[i][j] == 'W')
				set_spawn(config, i, j, &finded);
			j++;
		}
		i++;
	}
}

char	**copy_map(int fd, char *first_line)
{
	char	**strs;
	char	*to_add;

	strs = malloc(sizeof(char *) * 1);
	if (!strs)
		return (NULL);
	strs[0] = NULL;
	strs = add_strs_back(first_line, strs);
	if (!strs)
		return (NULL);
	while (1)
	{
		to_add = get_next_line(fd);
		if (to_add == NULL)
			break ;
		else if (ft_strcmp(to_add, "\n") == 0 && check_add(strs, to_add, fd))
			return (NULL);
		strs = add_strs_back(to_add, strs);
		if (!strs)
			break ;
	}
	close(fd);
	return (strs);
}

void	get_map(t_texture *config, char *buf, int fd)
{
	config->map = copy_map(fd, buf);
	if (!config->map)
		free_strs_texture_exit(config,
			"Error inside map or memory allocation fail.\n");
	find_spawn(config);
	if (verif_map(config) == false)
		free_strs_texture_exit(config, "Invalid map\n");
	verif_texture(config);
}
