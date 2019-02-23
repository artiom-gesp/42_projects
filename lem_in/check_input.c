/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:21:57 by agesp             #+#    #+#             */
/*   Updated: 2019/02/23 14:34:17 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*stop_read(char *str, int stop)
{
	int		i;
	char	*ret;

	i = 0;
	if (!str)
		return (NULL);
	while (stop > 0 && str[stop] != '\n')
		stop--;
	if (!(ret = malloc(sizeof(char) * stop + 1)))
		return (NULL);
	while (i < stop)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int		space_chr(char *str, int i)
{
	while (str[i] && str[i] != '\n' && str[i] != ' ')
		i++;
	if (str[i] == ' ')
		return (1);
	return (0);
}

int		mini_check(char *str, int *i, int *space, int *dash)
{
	while (str[*i] && str[*i] != '\n')
	{
		if ((*i == 0 || (*i > 0 && str[*i - 1] == '\n'))
					&& space_chr(str, *i))
		{
			while (str[*i] && str[*i] != '\n' && str[*i] != ' ')
				*i += 1;
			if (str[*i] != ' ')
				return (0);
		}
		while (ft_isdigit(str[*i]))
			*i += 1;
		if (str[*i] && str[*i] != '\n' && str[*i] != '-' && str[*i] != ' ')
			return (0);
		if (str[*i] == '-' && (*i += 1))
			*dash += 1;
		else if (str[*i] == ' ' && (*i += 1))
			*space += 1;
	}
	return (1);
}

int		check_digit(char *str, int *j)
{
	int		space;
	int		dash;
	int		i;
	int		name;

	space = 0;
	dash = 0;
	i = *j;
	name = 0;
	if (!mini_check(str, &i, &space, &dash))
		return (0);
	if ((space == 2 || dash == 1) && !ft_isdigit(str[i - 1]))
		return (0);
	if ((dash && space) || (!dash && space != 0 && space != 2)
			|| (!space && dash != 1 && dash != 0))
		return (0);
	*j = i;
	return (1);
}

char	*input_check(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	if (str[i] == 'L')
		return (stop_read(str, 0));
	while (str[i])
	{
		if (str[i] == '#')
			while (str[i] != '\n' && str[i])
				i++;
		else if (str[i] != 'L')
		{
			if (!check_digit(str, &i))
				return (stop_read(str, i - 1));
		}
		else
			return (stop_read(str, i - 1));
		if (str[i] && str[i] == '\n' && str[i + 1])
			i++;
	}
	return (str);
}
