/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 17:01:26 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/21 17:01:27 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	copy_path_texture(char **config_texture, char *buf)
{
	char	**tmp;

	tmp = ft_split(buf, ' ');
	if (ft_strlen_2d((const char **)tmp) != 2)
	{
		ft_free_strs(tmp);
		return (1);
	}
	*config_texture = ft_strdup(tmp[1]);
	ft_free_strs(tmp);
	return (0);
}

void	get_color(t_texture *config, char *buf, char way, int fd)
{
	char	**colors;
	char	*tmp;

	colors = ft_split(buf, ' ');
	if (ft_strlen_2d((const char **)colors) != 2)
	{
		ft_free_strs(colors);
		free_texture_exit(*config, buf, fd);
	}
	tmp = ft_strdup(colors[1]);
	ft_free_strs(colors);
	colors = ft_split(tmp, ',');
	ft_free((void *)&tmp);
	if (ft_strlen_2d((const char **)colors) != 3)
		free_texture_exit(*config, buf, fd);
	if (way == 'F')
		config->floor = convert_str_rgb_to_int(colors, *config, buf, fd);
	if (way == 'C')
		config->ceiling = convert_str_rgb_to_int(colors, *config, buf, fd);
}

int	check_config(t_texture *config, char *tmp, int fd)
{
	int	ret;

	ret = 0;
	if (ft_strlen(tmp) == 0)
	{
	}
	else if (ft_strncmp(tmp, "NO", 2) == 0 && config->no == NULL)
		ret += copy_path_texture(&config->no, tmp);
	else if (ft_strncmp(tmp, "SO", 2) == 0 && config->so == NULL)
		ret += copy_path_texture(&config->so, tmp);
	else if (ft_strncmp(tmp, "WE", 2) == 0 && config->we == NULL)
		ret += copy_path_texture(&config->we, tmp);
	else if (ft_strncmp(tmp, "EA", 2) == 0 && config->ea == NULL)
		ret += copy_path_texture(&config->ea, tmp);
	else if (ft_strncmp(tmp, "F", 1) == 0 && config->floor == -1)
		get_color(config, tmp, 'F', fd);
	else if (ft_strncmp(tmp, "C", 1) == 0 && config->ceiling == -1)
		get_color(config, tmp, 'C', fd);
	else
	{
		get_map(config, tmp, fd);
		return (-1);
	}
	ft_free((void *)&tmp);
	return (ret);
}

void	configuration(int fd, t_texture *config)
{
	char	*buf;
	char	*tmp;
	int		ret;	

	while (1)
	{
		buf = get_next_line(fd);
		if (!buf)
			free_texture_exit(*config, buf, fd);
		tmp = ft_strtrim(buf, " \n");
		ft_free((void *)&buf);
		ret = check_config(config, tmp, fd);
		if (ret == -1)
			break ;
		else if (ret > 0)
			free_texture_exit(*config, NULL, fd);
	}
}

void	map_check(char	*av, t_texture *config)
{
	int			fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		print_error_exit("Open error\n");
	configuration(fd, config);
}
