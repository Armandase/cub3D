/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:28:42 by adamiens          #+#    #+#             */
/*   Updated: 2023/03/18 13:32:22 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

void		extension_check(char *av);
void		parsing(int ac, char **av, t_texture *config);
void		print_error_exit(char *error);
void		map_check(char *map, t_texture *config);
long long	atoi_protect(char *str);
t_texture	init_texture(void);
void		free_texture_exit(t_texture config, char *buf, int fd);
int			convert_str_rgb_to_int(char **colors,
				t_texture config, char *buf, int fd);
void		get_map(t_texture *config, char *buf, int i);
bool		verif_map(t_texture *config);
void		verif_texture(t_texture *config);
void		free_strs_texture_exit(t_texture *config, char *error);
void		copy_texture_from_img_to_array(mlx_image_t *img, uint32_t ***img_tab, t_mlx *mlx, int max);

#endif
