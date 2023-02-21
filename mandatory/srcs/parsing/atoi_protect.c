/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_protect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adamiens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:04:35 by adamiens          #+#    #+#             */
/*   Updated: 2023/02/13 11:06:08 by adamiens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	atoi_protect(char *str)
{
	int			i;
	long long	value;

	i = 0;
	value = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + (str[i] - '0');
		i++;
		if (value > 2147483647)
			return (-1);
	}
	if ((value == 0 && i == 0) || str[i] != '\0')
		return (-1);
	return (value);
}
