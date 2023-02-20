/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:39:34 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/20 13:51:36 by ulayus           ###   ########.fr       */
/*                                                                            */ /* ************************************************************************** */
#ifndef RENDER_H
# define RENDER_H

# include "parsing.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h>
# include <float.h>
# include "../libs/mlx/mlx.h"

# define WIDTH 1080
# define HEIGHT 720
# define INF 1e30
# define ROTATION_SPEED 50
# define MOVEMENT_SPEED 0.1
# define LEFT 1
# define RIGHT 2

void	render(t_texture *config);
int		destroy_win(t_mlx *mlx);
int		handle_key(int keysym, t_mlx *mlx);
void	raycasting(t_mlx *mlx);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
double	ft_abs(double nb);
size_t	get_color_from_img(t_data *data, int x, int y);
void	texture_to_tab(t_texture *config, t_mlx *mlx);


#endif
