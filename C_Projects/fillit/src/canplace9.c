/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canplace9.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uroy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:26:48 by uroy              #+#    #+#             */
/*   Updated: 2018/11/29 15:42:34 by uroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	place9(int tab[][32], int i, int j, int c)
{
	tab[i][j] = c;
	tab[i + 1][j] = c;
	tab[i + 1][j + 1] = c;
	tab[i + 2][j] = c;
}

int		canplace9(int tab[][32], int i, int j, int c)
{
	if (tab[i + 2][0] == -1)
		return (0);
	while (j < 32 && (tab[i][j] != 0 || tab[i + 1][j] != 0
			|| tab[i + 1][j + 1] != 0
			|| tab[i + 2][j] != 0))
		j++;
	if (tab[i][j] == 0 && tab[i + 1][j] == 0
			&& tab[i + 1][j + 1] == 0
			&& tab[i + 2][j] == 0)
	{
		place9(tab, i, j, c);
		return (1);
	}
	return (canplace9(tab, i + 1, 0, c));
}
