/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:46:42 by agesp             #+#    #+#             */
/*   Updated: 2018/12/09 13:19:56 by uroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int				check_next(char **tab, int i, int j, int v)
{
	if (tab[i][j - 1] && tab[i][j - 1] == '#')
		v++;
	if (tab[i][j + 1] && tab[i][j + 1] == '#')
		v++;
	if (i - 1 >= 0 && tab[i - 1][j] == '#')
		v++;
	if (tab[i + 1] && tab[i + 1][j] && tab[i + 1][j] == '#')
		v++;
	return (v);
}

static int				check(char **tab, int i, int j, int v)
{
	while (tab[i])
	{
		j = -1;
		while (++j < 4)
			if (tab[i][j] == '#')
				v = check_next(tab, i, j, v);
		if ((i + 2) % 5 == 0 && i != 0)
		{
			if (v != 6 && v != 8)
				return (-1);
			v = 0;
			if (tab[i + 1])
				i++;
			i++;
		}
		else
		{
			i++;
			j = 0;
		}
	}
	return (1);
}

int						check_entry(char **tab)
{
	int		i;
	int		j;
	int		v;

	i = 0;
	j = 0;
	v = 0;
	return (check(tab, i, j, v));
}
