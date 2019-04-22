/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canplace3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uroy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:00:15 by uroy              #+#    #+#             */
/*   Updated: 2018/11/29 16:13:47 by uroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	place3(int tab[][32], int i, int j, int c)
{
	tab[i][j] = c;
	tab[i][j + 1] = c;
	tab[i + 1][j + 1] = c;
	tab[i + 1][j + 2] = c;
}

int		canplace3(int tab[][32], int i, int j, int c)
{
	if (tab[i + 1][0] == -1)
		return (0);
	while (j < 32 && (tab[i][j] != 0 || tab[i][j + 1] != 0
			|| tab[i + 1][j + 1] != 0
			|| tab[i + 1][j + 2] != 0))
		j++;
	if (tab[i][j] == 0 && tab[i][j + 1] == 0
			&& tab[i + 1][j + 1] == 0
			&& tab[i + 1][j + 2] == 0)
	{
		place3(tab, i, j, c);
		return (1);
	}
	return (canplace3(tab, i + 1, 0, c));
}
