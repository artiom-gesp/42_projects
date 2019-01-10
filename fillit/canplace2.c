/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canplace2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uroy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 17:55:54 by uroy              #+#    #+#             */
/*   Updated: 2018/12/06 15:19:01 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	place2(int tab[][32], int i, int j, int c)
{
	tab[i][j] = c;
	tab[i][j + 1] = c;
	tab[i][j + 2] = c;
	tab[i][j + 3] = c;
}

int		canplace2(int tab[][32], int i, int j, int c)
{
	if (tab[i][0] == -1)
		return (0);
	while (j < 32 && (tab[i][j] != 0 || tab[i][j + 1] != 0
			|| tab[i][j + 2] != 0
			|| tab[i][j + 3] != 0))
		j++;
	if (tab[i][j] == 0 && tab[i][j + 1] == 0
			&& tab[i][j + 2] == 0
			&& tab[i][j + 3] == 0)
	{
		place2(tab, i, j, c);
		return (1);
	}
	return (canplace2(tab, i + 1, 0, c));
}
