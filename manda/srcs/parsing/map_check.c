/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:59:08 by adamiens          #+#    #+#             */
/*   Updated: 2023/04/27 11:11:05 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include <fcntl.h>

static void	check_colors(char **colors, t_texture *config, char *buf, int fd)
{
	if (!colors)
		free_texture_exit(*config, buf, fd);
	if (ft_strlen_2d((const char **)colors) != 3)
	{
		ft_free_strs(colors);
		free_texture_exit(*config, buf, fd);
	}
}

void	get_color(t_texture *config, char *buf, char way, int fd)
{
	char	**colors;
	char	*tmp;

	colors = ft_split(buf, ' ');
	if (!colors)
		free_texture_exit(*config, buf, fd);
	if (ft_strlen_2d((const char **)colors) != 2)
	{
		ft_free_strs(colors);
		free_texture_exit(*config, buf, fd);
	}
	tmp = ft_strdup(colors[1]);
	if (!tmp)
		free_texture_exit(*config, buf, fd);
	ft_free_strs(colors);
	colors = ft_split(tmp, ',');
	ft_free((void *)&tmp);
	check_colors(colors, config, buf, fd);
	if (way == 'F')
		config->floor = convert_str_rgb_to_int(colors, *config, buf, fd);
	if (way == 'C')
		config->ceiling = convert_str_rgb_to_int(colors, *config, buf, fd);
}

int	check_config_extended(t_texture *config, char *tmp, int fd, char **buf)
{
	if (ft_strncmp(tmp, "F", 1) == 0 && config->floor == -1)
	{
		free(*buf);
		*buf = NULL;
		get_color(config, tmp, 'F', fd);
	}
	else if (ft_strncmp(tmp, "C", 1) == 0 && config->ceiling == -1)
	{
		free(*buf);
		*buf = NULL;
		get_color(config, tmp, 'C', fd);
	}
	else if (config->no && config->so && config->we && config->ea
		&& config->floor != -1 && config->ceiling != -1 && ft_strlen(tmp) != 0)
	{
		ft_free((void *)&tmp);
		get_map(config, *buf, fd);
		return (-1);
	}
	else if (ft_strcmp(*buf, "\n") != 0)
	{
		free(tmp);
		free_texture_exit(*config, *buf, fd);
	}
	return (0);
}

int	check_config(t_texture *config, char *tmp, int fd, char *buf)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(tmp, "NO", 2) == 0 && config->no == NULL)
		ret += copy_path_texture(&config->no, tmp);
	else if (ft_strncmp(tmp, "SO", 2) == 0 && config->so == NULL)
		ret += copy_path_texture(&config->so, tmp);
	else if (ft_strncmp(tmp, "WE", 2) == 0 && config->we == NULL)
		ret += copy_path_texture(&config->we, tmp);
	else if (ft_strncmp(tmp, "EA", 2) == 0 && config->ea == NULL)
		ret += copy_path_texture(&config->ea, tmp);
	else if (check_config_extended(config, tmp, fd, &buf) == -1)
		return (-1);
	if (buf)
		free(buf);
	ft_free((void *)&tmp);
	return (ret);
}

void	configuration(int fd, t_texture *config)
{
	char	*buf;
	char	*tmp;
	int		ret;	

	config->orientation = 0;
	while (1)
	{
		buf = get_next_line(fd);
		if (!buf)
			free_texture_exit(*config, buf, fd);
		tmp = ft_strtrim(buf, " \n");
		if (!tmp)
		{
			free(buf);
			free_texture_exit(*config, NULL, fd);
		}
		ret = check_config(config, tmp, fd, buf);
		if (ret == -1)
			break ;
		else if (ret > 0)
			free_texture_exit(*config, NULL, fd);
	}
}
