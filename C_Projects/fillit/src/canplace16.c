/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canplace16.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uroy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:42:40 by uroy              #+#    #+#             */
/*   Updated: 2018/12/10 13:25:48 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	place16(int tab[][32], int i, int j, int c)
{
	tab[i][j] = c;
	tab[i + 1][j] = c;
	tab[i][j + 1] = c;
	tab[i][j + 2] = c;
}

int		canplace16(int tab[][32], int i, int j, int c)
{
	if (tab[i + 1][0] == -1)
		return (0);
	while (j < 32 && (tab[i][j] != 0 || tab[i + 1][j] != 0
			|| tab[i][j + 1] != 0
			|| tab[i][j + 2] != 0))
		j++;
	if (tab[i][j] == 0 && tab[i + 1][j] == 0
			&& tab[i][j + 1] == 0
			&& tab[i][j + 2] == 0)
	{
		place16(tab, i, j, c);
		return (1);
	}
	return (canplace16(tab, i + 1, 0, c));
}
