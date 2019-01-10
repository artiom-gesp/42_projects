/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canplace1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uroy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:55:37 by uroy              #+#    #+#             */
/*   Updated: 2018/12/10 13:20:30 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	place1(int tab[][32], int i, int j, int c)
{
	tab[i][j] = c;
	tab[i + 1][j] = c;
	tab[i + 2][j] = c;
	tab[i + 3][j] = c;
}

int		canplace1(int tab[][32], int i, int j, int c)
{
	if (tab[i + 3][0] == -1)
		return (0);
	while (j < 32 && (tab[i][j] != 0 || tab[i + 1][j] != 0
			|| tab[i + 2][j] != 0
			|| tab[i + 3][j] != 0))
		j++;
	if (tab[i][j] == 0 && tab[i + 1][j] == 0
			&& tab[i + 2][j] == 0
			&& tab[i + 3][j] == 0)
	{
		place1(tab, i, j, c);
		return (1);
	}
	return (canplace1(tab, i + 1, 0, c));
}
