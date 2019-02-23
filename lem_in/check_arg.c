/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 11:43:09 by agesp             #+#    #+#             */
/*   Updated: 2019/02/23 11:49:22 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_end(char *str)
{
	int i;
	int pos;
	int count;
	int space;

	i = 0;
	pos = 0;
	count = 0;
	space = 0;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], "##end", 5))
		{
			count++;
			pos = i;
		}
		i++;
	}
	if (count == 0 || count > 1 || (str[i = pos + 6] && str[i] == '#'))
		return (-1);
	while (str[i] && str[i] != '\n')
		space += str[i++] == ' ' ? 1 : 0;
	return (space == 2 ? pos : -1);
}

int		is_start(char *str)
{
	int i;
	int pos;
	int count;
	int space;

	i = 0;
	pos = 0;
	count = 0;
	space = 0;
	while (str[i])
	{
		if (!ft_strncmp(&str[i], "##start", 7))
		{
			count++;
			pos = i;
		}
		i++;
	}
	if (count == 0 || count > 1 || (str[i = pos + 8] && str[i] == '#'))
		return (-1);
	while (str[i] && str[i] != '\n')
		space += str[i++] == ' ' ? 1 : 0;
	return (space == 2 ? pos : -1);
}

int		argument_check(char *str)
{
	int start_pos;
	int end_pos;

	if ((start_pos = is_start(str)) == -1)
		return (-1);
	if ((end_pos = is_end(str)) == -1)
		return (-1);
	return (1);
}
