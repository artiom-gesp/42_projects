/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canplace6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uroy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:18:27 by uroy              #+#    #+#             */
/*   Updated: 2018/12/10 11:39:56 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	place6(int tab[][32], int i, int j, int c)
{
	tab[i][j] = c;
	tab[i + 1][j] = c;
	tab[i + 1][j - 1] = c;
	tab[i + 2][j - 1] = c;
}

int		canplace6(int tab[][32], int i, int j, int c)
{
	if (tab[i + 2][0] == -1)
		return (0);
	while (j < 1)
		j++;
	while (j < 32 && (tab[i][j] != 0 || tab[i + 1][j] != 0
			|| tab[i + 1][j - 1] != 0
			|| tab[i + 2][j - 1] != 0))
		j++;
	if (tab[i][j] == 0 && tab[i + 1][j] == 0
			&& tab[i + 1][j - 1] == 0
			&& tab[i + 2][j - 1] == 0)
	{
		place6(tab, i, j, c);
		return (1);
	}
	return (canplace6(tab, i + 1, 0, c));
}
