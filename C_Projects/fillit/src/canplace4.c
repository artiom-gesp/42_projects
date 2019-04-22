/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canplace4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uroy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:11:47 by uroy              #+#    #+#             */
/*   Updated: 2018/12/10 13:06:10 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	place4(int tab[][32], int i, int j, int c)
{
	tab[i][j] = c;
	tab[i][j + 1] = c;
	tab[i + 1][j] = c;
	tab[i + 1][j - 1] = c;
}

int		canplace4(int tab[][32], int i, int j, int c)
{
	if (tab[i + 1][0] == -1)
		return (0);
	while (j < 1)
		j++;
	while (j < 32 && (tab[i][j] != 0
			|| tab[i][j + 1] != 0
			|| tab[i + 1][j] != 0
			|| tab[i + 1][j - 1] != 0))
		j++;
	if (tab[i][j] == 0 && tab[i][j + 1] == 0
			&& tab[i + 1][j] == 0
			&& tab[i + 1][j - 1] == 0)
	{
		place4(tab, i, j, c);
		return (1);
	}
	return (canplace4(tab, i + 1, 0, c));
}
