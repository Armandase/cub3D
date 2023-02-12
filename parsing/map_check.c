#include "parsing.h"
#include <fcntl.h>

int	copy_path_texture(char **config_texture, char *buf, char *dir)
{
	char	*tmp;

	tmp = ft_strjoin(dir, " ./");
	if (ft_strncmp(buf, tmp, 5) != 0)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	tmp = ft_strchr(buf, '/');
	tmp = ft_strtrim(&tmp[1], "\n");
	*config_texture = ft_strdup(tmp);
	free(tmp);
	return (0);
}

t_texture	init_texture(void)
{
	t_texture	config;

	config.ceiling = 0;
	config.floor = 0;
	config.no = NULL;
	config.ea = NULL;
	config.so = NULL;
	config.we = NULL;
	return (config);
}

void	free_exit_config(t_texture config)
{
	if (config.no != NULL)
		free(config.no);
	if (config.so != NULL)
		free(config.so);
	if (config.we != NULL)
		free(config.we);
	if (config.ea != NULL)
		free(config.ea);
	print_error_exit("Configuration error\n");
}

int	get_color(t_config, char *str)
{

}

t_texture	configuration(int fd)
{
	int			i;
	int			check;
	char		*buf;
	t_texture	config;

	config = init_texture();
	i = 0;
	check = 0;
	while (i < 7)
	{
		buf = get_next_line(fd);
		if ((buf == NULL && i != 4) || ft_strlen(buf) < 7 || check > 0)
		{
			if (buf)
				free(buf);
			free_exit_config(config);
		}
		if (i == 0)
			check += copy_path_texture(&config.no, buf, "NO");
		if (i == 1)
			check += copy_path_texture(&config.so, buf, "SO");
		if (i == 2)
			check += copy_path_texture(&config.we, buf, "WE");
		if (i == 3)
			check += copy_path_texture(&config.ea, buf, "EA");
		if (i == 5)
			check += get_color(config, "F");
		i++;
		free(buf);
	}
	if (check > 0)
		free_exit_config(config);
	return (config);
}

#include <stdio.h>

void	map_check(char	*map)
{
	int			fd;
	t_texture	config;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		print_error_exit("Open error\n");
	config = configuration(fd);
	printf("no:%s\nso:%s\nea:%s\nwe:%s\n", config.no, config.so, config.ea, config.we);
	free(config.no);
	free(config.so);
	free(config.ea);
	free(config.we);
}
