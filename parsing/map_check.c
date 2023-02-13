#include "parsing.h"
#include <fcntl.h>

void	ft_free(void	**addr)
{
	if (*addr)
	{
		free(*addr);
		*addr = NULL;
	}
}

int	copy_path_texture(char **config_texture, char *buf, char *dir)
{
	char	*tmp;

	tmp = ft_strjoin(dir, " ./");
	if (ft_strncmp(buf, tmp, 5) != 0)
	{
		ft_free((void *)&tmp);
		return (1);
	}
	ft_free((void *)&tmp);
	tmp = ft_strchr(buf, '/');
	tmp = ft_strtrim(&tmp[1], "\n");
	*config_texture = ft_strdup(tmp);
	ft_free((void *)&tmp);
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

void	free_exit_config(t_texture config, char *buf)
{
	if (config.no != NULL)
		ft_free((void *)&config.no);
	if (config.so != NULL)
		ft_free((void *)&config.so);
	if (config.we != NULL)
		ft_free((void *)&config.we);
	if (config.ea != NULL)
		ft_free((void *)&config.ea);
	if (buf)
		ft_free((void *)&buf);
	print_error_exit("Configuration error\n");
}

int	convert_str_rgb_to_int(char **colors, t_texture config, char *buf)
{
	int	r;
	int	g;
	int	b;
	int	sum;

	r = atoi_protect(colors[0]);
	g = atoi_protect(colors[1]);
	b = atoi_protect(colors[2]);
	if (r == -1 || g == -1 || b == -1)
	{
		ft_free_strs(colors);
		free_exit_config(config, buf);
	}
	sum = (r * 256 * 256) + (g * 256) + b;
	return (sum);
}

int	get_color(t_texture config, char *buf, char way)
{
	char	**colors;
	char	*tmp;

	if (buf[0] && buf[0] == way && buf[1] && buf[1] == ' ')
	{
		tmp = ft_strdup(&buf[2]);
		colors = ft_split(tmp, ',');
		ft_free((void *)&tmp);
		if (ft_strlen_2d((const char **)colors) != 3)
			free_exit_config(config, buf);
		if (way == 'F')
			config.floor = convert_str_rgb_to_int(colors, config, buf);
		if (way == 'C')
			config.ceiling = convert_str_rgb_to_int(colors, config, buf);
	}
	else
		free_exit_config(config, buf);
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
			free_exit_config(config, buf);
		if (i == 0)
			check += copy_path_texture(&config.no, buf, "NO");
		if (i == 1)
			check += copy_path_texture(&config.so, buf, "SO");
		if (i == 2)
			check += copy_path_texture(&config.we, buf, "WE");
		if (i == 3)
			check += copy_path_texture(&config.ea, buf, "EA");
		if (i == 5)
			get_color(config, buf, 'F');
		if (i == 6)
			get_color(config, buf, 'C');
		i++;
		ft_free((void *)&buf);
	}
	if (check > 0)
		free_exit_config(config, buf);
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
	ft_free((void *)&config.no);
	ft_free((void *)&config.so);
	ft_free((void *)&config.ea);
	ft_free((void *)&config.we);
}
