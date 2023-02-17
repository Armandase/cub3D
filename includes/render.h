/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:39:34 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/17 16:40:23 by ulayus           ###   ########.fr       */
/*                                                                            */ /* ************************************************************************** */
#ifndef RENDER_H
# define RENDER_H

# include "parsing.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include "../libs/mlx/mlx.h"

# define WIDTH 1080
# define HEIGHT 720

void	render(t_texture *config);
int		destroy_win(t_mlx *mlx);
int		handle_key(int keysym, t_mlx *mlx);

#endif
