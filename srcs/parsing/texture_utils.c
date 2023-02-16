/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:21:32 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/16 09:31:30 by adamiens         ###   ########.fr       */
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
		free_texture_exit(config, buf, fd);
	}
	sum = (r * 100000) + (g * 1000) + b;
	ft_free_strs(colors);
	return (sum);
}
