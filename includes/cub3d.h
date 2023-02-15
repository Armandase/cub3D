/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:18:41 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/15 11:02:16 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include <math.h>

typedef struct s_texture{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceiling;
}	t_texture;

typedef struct s_map{
	char	**map;
}t_map;

void	ft_free(void **addr);

#endif
