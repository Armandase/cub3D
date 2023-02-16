/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:06:14 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/16 09:07:05 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	max_line_length(char **map)
{
	int	i;
	int	j;
	int	length;

	length = 0;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j])
		{
			j++;
		}
		if (j > length)
			length = j;
		i++;
	}
	return (length);
}

static void	check_line_format(char *line, int max_length)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
	{
	}
}

void	verif_map(t_texture *config)
{
	const int	max_length = max_line_length(config->map);
	const char	**map = config->map;
	int			i;
	int			j;

	i = 0;
	while (map[i] != NULL)
	{
		check_line_format(map[i], max_length);
	}
}
