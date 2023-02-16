/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 09:39:34 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/16 13:53:44 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "parsing.h"
# include "../libs/mlx/mlx.h"

# define WIDTH 1080
# define HEIGHT 720

typedef struct s_mlx
{
	void	*init;
	void	*win;
	void	*img;
	char	*img_addr;
	int		img_width;
	int		img_height;
	int		bits_per_px;
	int		line_len;
	int		endian;
}	t_mlx;

void	render(t_texture *config);

#endif
