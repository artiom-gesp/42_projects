/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recon_tetr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 11:15:09 by agesp             #+#    #+#             */
/*   Updated: 2018/12/09 13:33:55 by uroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	is_bc(int tab[], char **tetr, int i, int pos)
{
	int j;

	j = 0;
	while (tetr[i] && tetr[i][j] && tetr[i][j] != '#')
	{
		j++;
	}
	if (tetr[i + 3] && tetr[i + 1][j] == '#'
			&& tetr[i + 2][j] == '#' && tetr[i + 3][j] == '#')
		tab[pos] = 1;
	if (tetr[i] && tetr[i][j + 1] == '#'
			&& tetr[i][j + 2] == '#' && tetr[i][j + 3] == '#')
		tab[pos] = 2;
}

void	is_z(int tab[], char **tetr, int i, int pos)
{
	int j;

	j = 0;
	while (tetr[i] && tetr[i][j] && tetr[i][j] != '#')
	{
		j++;
	}
	if (tetr[i + 1] && tetr[i][j + 1] == '#' && tetr[i + 1][j + 1] == '#'
			&& tetr[i + 1][j + 2] == '#')
		tab[pos] = 3;
	if (tetr[i + 1] && tetr[i][j + 1] == '#' && tetr[i + 1][j] == '#'
			&& tetr[i + 1][j - 1] == '#')
		tab[pos] = 4;
	if (tetr[i + 2] && tetr[i + 1][j] == '#' && tetr[i + 1][j + 1] == '#'
			&& tetr[i + 2][j + 1] == '#')
		tab[pos] = 5;
	if (tetr[i + 2] && tetr[i + 1][j] == '#' && tetr[i + 1][j - 1] == '#'
			&& tetr[i + 2][j - 1] == '#')
		tab[pos] = 6;
}

void	is_mp(int tab[], char **tetr, int i, int pos)
{
	int j;

	j = 0;
	while (tetr[i] && tetr[i][j] && tetr[i][j] != '#')
	{
		j++;
	}
	if (tetr[i + 1] && tetr[i + 1][j] == '#' && tetr[i + 1][j + 1] == '#'
			&& tetr[i + 1][j - 1] == '#')
		tab[pos] = 7;
	if (tetr[i + 1] && tetr[i][j + 1] == '#' && tetr[i][j + 2] == '#'
			&& tetr[i + 1][j + 1] == '#')
		tab[pos] = 8;
	if (tetr[i + 2] && tetr[i + 1][j] == '#' && tetr[i + 1][j + 1] == '#'
			&& tetr[i + 2][j] == '#')
		tab[pos] = 9;
	if (tetr[i + 2] && tetr[i + 1][j] == '#' && tetr[i + 1][j - 1] == '#'
			&& tetr[i + 2][j] == '#')
		tab[pos] = 10;
}

void	is_l(int tab[], char **tetr, int i, int pos)
{
	int j;

	j = 0;
	while (tetr[i] && tetr[i][j] && tetr[i][j] != '#')
	{
		j++;
	}
	if (tetr[i + 2] && tetr[i][j + 1] == '#' && tetr[i + 1][j] == '#'
			&& tetr[i + 2][j] == '#')
		tab[pos] = 11;
	if (tetr[i + 1] && tetr[i + 1][j] == '#' && tetr[i + 1][j + 1] == '#'
			&& tetr[i + 1][j + 2] == '#')
		tab[pos] = 12;
	if (tetr[i + 2] && tetr[i + 1][j] == '#' && tetr[i + 2][j] == '#'
			&& tetr[i + 2][j - 1] == '#')
		tab[pos] = 13;
	if (tetr[i + 1] && tetr[i][j + 1] == '#' && tetr[i][j + 2] == '#'
			&& tetr[i + 1][j + 2] == '#')
		tab[pos] = 14;
}

void	is_rev_l(int tab[], char **tetr, int i, int pos)
{
	int		j;

	j = 0;
	while (tetr[i] && tetr[i][j] && tetr[i][j] != '#')
	{
		j++;
	}
	if (tetr[i + 2] && tetr[i][j + 1] == '#' && tetr[i + 1][j + 1] == '#'
			&& tetr[i + 2][j + 1] == '#')
		tab[pos] = 15;
	if (tetr[i + 1] && tetr[i + 1][j] == '#' && tetr[i][j + 1] == '#'
			&& tetr[i][j + 2] == '#')
		tab[pos] = 16;
	if (tetr[i + 2] && tetr[i + 1][j] == '#' && tetr[i + 2][j] == '#'
			&& tetr[i + 2][j + 1] == '#')
		tab[pos] = 17;
	if (tetr[i + 1] && tetr[i + 1][j] == '#' && tetr[i + 1][j - 1] == '#'
			&& tetr[i + 1][j - 2] == '#')
		tab[pos] = 18;
}
