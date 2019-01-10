/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tetraminos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 11:15:00 by agesp             #+#    #+#             */
/*   Updated: 2018/12/10 13:43:48 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	is_sqare(int tab[], char **tetr, int i, int pos)
{
	int j;

	j = 0;
	while (tetr[i] && tetr[i][j] && tetr[i][j] != '#')
	{
		j++;
	}
	if (tetr[i + 1] && tetr[i + 1][j] == '#' && tetr[i][j + 1] == '#'
			&& tetr[i + 1][j + 1] == '#')
		tab[pos] = 19;
}

void	extr_tetr(char **tetr, int tab[])
{
	int i;
	int pos;

	i = 0;
	pos = 0;
	while (tetr[i])
	{
		if ((i + 1) % 5 == 0 && i != 0)
		{
			if (tetr[i + 2])
				i += 1;
			pos++;
		}
		is_bc(tab, tetr, i, pos);
		is_z(tab, tetr, i, pos);
		is_mp(tab, tetr, i, pos);
		is_l(tab, tetr, i, pos);
		is_rev_l(tab, tetr, i, pos);
		is_sqare(tab, tetr, i, pos);
		i++;
	}
}
