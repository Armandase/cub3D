/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:18:41 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/12 10:35:48 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "./parsing/parsing.h"
# include <math.h>

typedef struct s_texture{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceiling;
}	t_texture;

#endif
