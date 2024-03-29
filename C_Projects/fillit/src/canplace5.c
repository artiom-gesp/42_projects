/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canplace5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uroy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:16:03 by uroy              #+#    #+#             */
/*   Updated: 2018/11/29 16:55:52 by uroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	place5(int tab[][32], int i, int j, int c)
{
	tab[i][j] = c;
	tab[i + 1][j] = c;
	tab[i + 1][j + 1] = c;
	tab[i + 2][j + 1] = c;
}

int		canplace5(int tab[][32], int i, int j, int c)
{
	if (tab[i + 2][0] == -1)
		return (0);
	while (j < 32 && (tab[i][j] != 0 || tab[i + 1][j] != 0
			|| tab[i + 1][j + 1] != 0
			|| tab[i + 2][j + 1] != 0))
		j++;
	if (tab[i][j] == 0 && tab[i + 1][j] == 0
			&& tab[i + 1][j + 1] == 0
			&& tab[i + 2][j + 1] == 0)
	{
		place5(tab, i, j, c);
		return (1);
	}
	return (canplace5(tab, i + 1, 0, c));
}
