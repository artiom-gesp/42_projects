/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canplace14.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uroy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:39:00 by uroy              #+#    #+#             */
/*   Updated: 2018/12/10 13:26:06 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	place14(int tab[][32], int i, int j, int c)
{
	tab[i][j] = c;
	tab[i][j + 1] = c;
	tab[i][j + 2] = c;
	tab[i + 1][j + 2] = c;
}

int		canplace14(int tab[][32], int i, int j, int c)
{
	if (tab[i + 1][0] == -1)
		return (0);
	while (j < 32 && (tab[i][j] != 0 || tab[i][j + 1] != 0
			|| tab[i][j + 2] != 0
			|| tab[i + 1][j + 2] != 0))
		j++;
	if (tab[i][j] == 0 && tab[i][j + 1] == 0
			&& tab[i][j + 2] == 0
			&& tab[i + 1][j + 2] == 0)
	{
		place14(tab, i, j, c);
		return (1);
	}
	return (canplace14(tab, i + 1, 0, c));
}
