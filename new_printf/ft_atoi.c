/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 10:59:28 by agesp             #+#    #+#             */
/*   Updated: 2018/11/09 11:22:46 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_atoi(int is_negative, int save)
{
	if (is_negative == 1)
		return (save * -1);
	else
		return (save);
}

static int	special_car(const char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\r'
			|| str[i] == '\f' || str[i] == '\n')
		i++;
	return (i);
}

int			ft_atoi(const char *str)
{
	int i;
	int save;
	int is_negative;

	i = special_car(str);
	is_negative = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			is_negative = 1;
		}
		i++;
	}
	save = 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		save = save * 10;
		save = save + (str[i] - '0');
		i++;
	}
	return (print_atoi(is_negative, save));
}
