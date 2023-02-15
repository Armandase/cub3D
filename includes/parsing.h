/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 17:28:42 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/13 11:07:01 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../cub3d.h"

void		extension_check(char *av);
void		parsing(int ac, char **av);
void		print_error_exit(char *error);
void		map_check(char *map);
long long	atoi_protect(char *str);

#endif
