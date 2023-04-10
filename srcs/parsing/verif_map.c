/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:06:14 by adamiens          #+#    #+#             */
/*   Updated: 2023/04/10 09:08:48 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

#include <stdio.h>

bool	check_char(const char **map, int i, int j, t_texture *config)
{
	bool	valid;

	valid = true;
	if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'D' && ft_isspace(map[i][j])
			== false && map[i][j] != config->orientation && map[i][j] != '\n')
		valid = false;
	else if (ft_isspace(map[i][j]) == true && !(map[i + 1] != NULL
		&& (map[i + 1][j] == '1' || ft_isspace(map[i + 1][j]))))
	{
		if (map[i + 1])
			valid = false;
	}
	else if (i == 0 && map[i][j] != '1' && ft_isspace(map[i][j]) == false
			&& map[i][j] != '\n')
		valid = false;
	else if ((map[i][j] == '0' || map[i][j] == 'D')
			&& (map[i][j + 1] == '\n' || map[i][j + 1] == ' '))
		valid = false;
	else if (ft_isspace(map[i][j]) && (map[i][j + 1] == '0' || map[i][j + 1] == 'D'))
		valid = false;
	else if (map[i][j] == '0' && !(map[i + 1] != NULL
		&& (map[i + 1][j] == '1' || map[i + 1][j] == '0'
			|| map[i + 1][j] == config->orientation || map[i + 1][j] == 'D')))
		valid = false;
	return (valid);
}

bool	verif_map(t_texture *config)
{
	const char	**map = (const char **)config->map;
	bool		valid;
	int			i;
	int			j;

	i = 0;
	valid = true;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j])
		{
			valid = check_char(map, i, j, config);
			if (valid == false)
				return (valid);
			j++;
		}
		i++;
	}
	if (!config->orientation)
		valid = false;
	return (valid);
}
