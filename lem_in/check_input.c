/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:21:57 by agesp             #+#    #+#             */
/*   Updated: 2019/02/20 16:50:13 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_digit(char *str, int *j)
{
	int		space;
	int		dash;
	int		i;

	space = 0;
	dash = 0;
	i = *j;
	while (str[i] && str[i] != '\n')
	{
		while (ft_isdigit(str[i]))
			i++;
		if (str[i] && str[i] != '\n' && str[i] != '-' && str[i] != ' ')
			return (0);
		if (str[i] == '-' && i++)
			dash++;
		else if (str[i] == ' ' && i++)
			space++;
	}
	if ((dash && space) || (!dash && space != 0 && space != 2)
			|| (!space && dash != 1 && dash != 0))
		return (0);
	*j = i;
	return (1);
}


int		input_check(char *str)
{
	int		i;
	int		space;
	int		dash;

	i = 0;
	if (!str)
		return (0);
	if (str[i] != '#' && !ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		space = 0;
		dash = 0;
		if (str[i] == '#')
			while (str[i] != '\n' && str[i])
				i++;
		else if (ft_isdigit(str[i]) && !check_digit(str, &i))
			return (0);
		else
			return (0);
		if (str[i] && str[i] == '\n' && str[i + 1])
			i++;
	}
	return (1);
}
