/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canplace13.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uroy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:37:41 by uroy              #+#    #+#             */
/*   Updated: 2018/12/10 13:26:16 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	place13(int tab[][32], int i, int j, int c)
{
	tab[i][j] = c;
	tab[i + 1][j] = c;
	tab[i + 2][j] = c;
	tab[i + 2][j - 1] = c;
}

int		canplace13(int tab[][32], int i, int j, int c)
{
	if (tab[i + 2][0] == -1)
		return (0);
	while (j < 1)
		j++;
	while (j < 32 && (tab[i][j] != 0 || tab[i + 1][j] != 0
			|| tab[i + 2][j] != 0
			|| tab[i + 2][j - 1] != 0))
		j++;
	if (tab[i][j] == 0 && tab[i + 1][j] == 0
			&& tab[i + 2][j] == 0
			&& tab[i + 2][j - 1] == 0)
	{
		place13(tab, i, j, c);
		return (1);
	}
	return (canplace13(tab, i + 1, 0, c));
}
