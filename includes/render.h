/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:46:44 by adamiens          #+#    #+#             */
/*   Updated: 2023/04/11 14:48:50 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "parsing.h"
# include <pthread.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h>
# include <float.h>

# define WIDTH 1080
# define HEIGHT 720
# define INF 1e30
# define ROTATION_SPEED 40
# define MOVEMENT_SPEED 0.08
# define MAX_ITERATIONS 2500
# define LEFT 1
# define RIGHT 2
# define SQUARE_SIZE 5
# define POS_X 1
# define POS_Y -1

void		render(t_texture *config);
int			destroy_win(t_mlx *mlx);
void		handle_key_released(mlx_key_data_t keydata, void *param);
void		handle_key(void	*param);
void		mouse_hook_camera(void *data);
void		raycasting(t_mlx *mlx);
double		ft_abs(double nb);
uint32_t	get_color_from_img(mlx_image_t *img, int x, int y);
void		texture_to_tab(t_texture *config, t_mlx *mlx);
void		animation_sprite(t_texture *config, t_mlx *mlx);
void		put_sprite_to_img(t_mlx *mlx, int x, t_dda *dda, t_raycast *info);
void		put_sprite_to_img_animation(t_mlx *mlx, int x, t_dda *dda,
				t_raycast *info);
void		rotate_vectors(t_mlx *mlx, int flag);
void		minimap(t_mlx *mlx);
void		anim(t_mlx *mlx);
void		get_animation(t_texture *config, t_mlx *mlx);
void		hourglass(t_mlx *mlx);
void		free_render_exit(t_texture *config, t_mlx *mlx, char *error);
void		free_all(t_texture *config);
void		set_icon(t_mlx *mlx, t_texture *config);
void		init_raycast(t_mlx *mlx);
void		init_direction_vectors(t_mlx *mlx);
void		init_dda(t_dda *dda, t_raycast *info, t_mlx *mlx);
void		init_side_dist_in_dda(t_dda *dda, t_mlx *mlx, t_raycast *info);
int			select_texture(t_raycast *info, t_dda dda, int side);
bool		check_wall(t_mlx *mlx, t_dda *dda);
void		check_door(t_mlx *mlx, t_dda *dda, char tile, bool *hit);

#endif
