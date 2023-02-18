/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:06:14 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/18 18:08:16 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

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
			if (map[i][j] != '1' && map[i][j] != '0' && ft_isspace(map[i][j]) == false && map[i][j] != config->orientation && map[i][j] != '\n')
				valid = false;
			else if (ft_isspace(map[i][j]) == true && !(map[i + 1] != NULL
				&& (map[i + 1][j] == '1' || ft_isspace(map[i + 1][j]))))
			{
				if (map[i + 1])
					valid = false;
			}
			else if (i == 0 && map[i][j] != '1' && ft_isspace(map[i][j]) == false)
				valid = false;
			else if (map[i][j] == '0' && map[i][j + 1] == '\n')
				valid = false;
			else if (ft_isspace(map[i][j]) && map[i][j + 1] == '0')
				valid = false;
			else if (map[i][j] == '0' && !(map[i + 1] != NULL
				&& (map[i + 1][j] == '1' || map[i + 1][j] == '0' || map[i + 1][j] == config->orientation)))
				valid = false;
			j++;
		}
		i++;
	}
	return (valid);
}
