/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:59:08 by adamiens          #+#    #+#             */
/*   Updated: 2023/04/11 10:05:05 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include <fcntl.h>

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
	if (!colors)
		free_texture_exit(*config, buf, fd);
	if (ft_strlen_2d((const char **)colors) != 3)
		free_texture_exit(*config, buf, fd);
	if (way == 'F')
		config->floor = convert_str_rgb_to_int(colors, *config, buf, fd);
	if (way == 'C')
		config->ceiling = convert_str_rgb_to_int(colors, *config, buf, fd);
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
	else if (ft_strncmp(tmp, "F", 1) == 0 && config->floor == -1)
		get_color(config, tmp, 'F', fd);
	else if (ft_strncmp(tmp, "C", 1) == 0 && config->ceiling == -1)
		get_color(config, tmp, 'C', fd);
	else if (config->no && config->so && config->we && config->ea
		&& config->floor != -1 && config->ceiling != -1 && ft_strlen(tmp) != 0)
	{
		ft_free((void *)&tmp);
		get_map(config, buf, fd);
		return (-1);
	}
	ft_free((void *)&buf);
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

void	map_check(char	*av, t_texture *config)
{
	int			fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		print_error_exit("Open error\n");
	configuration(fd, config);
	verif_path_texture(config);
}
