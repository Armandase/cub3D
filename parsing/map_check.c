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
	if (r == -1 || g == -1 || b == -1 || r > 256 || g > 256 || b > 256)
	{
		ft_free_strs(colors);
		free_exit_config(config, buf);
	}
	sum = (r * 100000) + (g * 1000) + b;
	ft_free_strs(colors);
	return (sum);
}

void	get_color(t_texture *config, char *buf, char way)
{
	char	**colors;
	char	*tmp;
	char	*cpy;

	if (buf[0] && buf[0] == way && buf[1] && buf[1] == ' ')
	{
		tmp = ft_strdup(&buf[2]);
		cpy = malloc(sizeof(char) * ft_strlen(tmp));
		ft_strlcpy(cpy, tmp, ft_strlen(tmp));
		colors = ft_split(cpy, ',');
		ft_free((void *)&tmp);
		ft_free((void *)&cpy);
		if (ft_strlen_2d((const char **)colors) != 3)
			free_exit_config(*config, buf);
		if (way == 'F')
			config->floor = convert_str_rgb_to_int(colors, *config, buf);
		if (way == 'C')
			config->ceiling = convert_str_rgb_to_int(colors, *config, buf);
	}
	else
		free_exit_config(*config, buf);
}

void	configuration(int fd, t_texture *config, t_map *map)
{
	int			check;
	char		*buf;

	while (1)
	{
		buf = get_next_line(fd);
		if (buf && ft_strncmp(buf, "NO", 2) == 0)
			copy_path_texture(&config->no, buf, "NO");
		else if (buf && ft_strncmp(buf, "SO", 2) == 0)
			copy_path_texture(&config->so, buf, "SO");
		else if (buf && ft_strncmp(buf, "WE", 2) == 0)
			copy_path_texture(&config->we, buf, "WE");
		else if (buf && ft_strncmp(buf, "EA", 2) == 0)
			copy_path_texture(&config->ea, buf, "EA");
		else if (buf && ft_strncmp(buf, "F", 1) == 0)
			get_color(config, buf, 'F');
		else if (buf && ft_strncmp(buf, "C", 2) == 0)
			get_color(config, buf, 'C');
		ft_free((void *)&buf);
	}
}

void	map_check(char	*av)
{
	int			fd;
	t_texture	config;
	t_map		map;

	fd = open(av, O_RDONLY);
	config = init_texture();
	map.map = NULL;
	if (fd < 0)
		print_error_exit("Open error\n");
	configuration(fd, &config, &map);

	ft_printf("no:%s\nso:%s\nea:%s\nwe:%s\nfloor:%d\nceiling:%d\n", config.no, config.so, config.ea, config.we, config.floor, config.ceiling);
	ft_free((void *)&config.no);
	ft_free((void *)&config.so);
	ft_free((void *)&config.ea);
	ft_free((void *)&config.we);
}
