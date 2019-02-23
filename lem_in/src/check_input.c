/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:21:57 by agesp             #+#    #+#             */
/*   Updated: 2019/02/23 17:03:32 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lem_in.h"

int		is_com(char *str)
{
	if (str[0] && str[0] == '#')
		return (1);
	return (0);
}

int		is_room(char *str)
{
	int i;

	i = -1;
	while (str[++i] && str[i] != ' ');
	if (!str[i])
		return (0);
	while (ft_isdigit(str[++i]));
	if (str[i++] != ' ')
		return (0);
	while (ft_isdigit(str[i++]));
	if (str[i])
		return (0);
	return (1);
}

int		is_ant(char *str)
{
	int i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

int		is_link(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '-')
		i++;
	if (!str[i])
		return (0);
	if (str[i + 1] == 'L' || !str[i + 1])
		return (0);
	return (1);
}

int		get_dasp(char *str)
{
	int i;
	int space;
	int dash;

	i = 0;
	space = 0;
	dash = 0;
	if (str[0] == 'L')
		return (0);
	while (str[i])
	{
		if (str[i] == ' ')
			space++;
		if (str[i] == '-')
			dash++;
		i++;
	}
	if ((dash && space) || (!dash && space != 2)
			|| (!space && dash != 1))
		return (0);
	return (1);
}

int		input_check(t_arg *l)
{
	int		i;

	i = 0;
	while (l)
	{
		if (is_com(l->arg) || is_ant(l->arg))
		{
			l = l->next;
			i++;
		}
		else if (get_dasp(l->arg))
		{
			if (is_link(l->arg) || is_room(l->arg))
			{
				l = l->next;
				i++;
			}
			else
				return (i);
		}
		else
			return (i);
	}
	return (-1);
}
