/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:21:32 by adamiens          #+#    #+#             */
/*   Updated: 2023/03/03 12:47:09 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_texture	init_texture(void)
{
	t_texture	config;

	config.ceiling = -1;
	config.floor = -1;
	config.no = NULL;
	config.ea = NULL;
	config.so = NULL;
	config.we = NULL;
	config.map = NULL;
	return (config);
}

void	free_texture_exit(t_texture config, char *buf, int fd)
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
	if (fd > 0)
		close (fd);
	print_error_exit("Configuration error\n");
}

int	convert_str_rgb_to_int(char **colors, t_texture config, char *buf, int fd)
{
	int				r;
	int				g;
	int				b;
	long			sum;

	r = atoi_protect(colors[0]);
	g = atoi_protect(colors[1]);
	b = atoi_protect(colors[2]);
	if (r == -1 || g == -1 || b == -1 || r > 255 || g > 255 || b > 255)
	{
		ft_free_strs(colors);
		free_texture_exit(config, buf, fd);
	}
	sum = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	ft_free_strs(colors);
	return (sum);
}

void	free_strs_texture_exit(t_texture *config, char *error)
{
	if (config->so)
		free(config->so);
	if (config->no)
		free(config->no);
	if (config->ea)
		free(config->ea);
	if (config->we)
		free(config->we);
	ft_free_strs(config->map);
	print_error_exit(error);
}

void	verif_texture(t_texture *config)
{
	char	*extend;

	extend = ft_strnstr(config->so, ".xpm42", ft_strlen(config->so));
	if (!extend || ft_strlen(extend) > ft_strlen(".xpm42"))
		free_strs_texture_exit(config, "Our cub3d only works with xpm42\n");
	extend = ft_strnstr(config->no, ".xpm42", ft_strlen(config->no));
	if (!extend || ft_strlen(extend) > ft_strlen(".xpm42"))
		free_strs_texture_exit(config, "Our cub3d only works with xpm42\n");
	extend = ft_strnstr(config->we, ".xpm42", ft_strlen(config->we));
	if (!extend || ft_strlen(extend) > ft_strlen(".xpm42"))
		free_strs_texture_exit(config, "Our cub3d only works with xpm42\n");
	extend = ft_strnstr(config->ea, ".xpm42", ft_strlen(config->ea));
	if (!extend || ft_strlen(extend) > ft_strlen(".xpm42"))
		free_strs_texture_exit(config, "Our cub3d only works with xpm42\n");
}
