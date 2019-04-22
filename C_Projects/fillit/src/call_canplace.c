/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uroy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 11:28:39 by uroy              #+#    #+#             */
/*   Updated: 2018/12/09 13:11:35 by uroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		get_letter(int tab[][32])
{
	int		i;
	int		j;
	int		ret;
	int		save;

	i = 0;
	j = 0;
	ret = 1;
	save = 0;
	while (tab[i][0] != -1 && i < 32)
	{
		j = 0;
		while (tab[i][j] != -1 && j < 32)
		{
			if (tab[i][j] > save)
				save = tab[i][j];
			j++;
		}
		i++;
	}
	if (save != 0)
		return (save + 1);
	return (ret);
}

static int		solve_cord(int to_fill[][32], int tetr, int i, int j)
{
	int	c;

	c = get_letter(to_fill);
	if (tetr == 1)
		return (canplace1(to_fill, i, j, c));
	if (tetr == 2)
		return (canplace2(to_fill, i, j, c));
	if (tetr == 3)
		return (canplace3(to_fill, i, j, c));
	if (tetr == 4)
		return (canplace4(to_fill, i, j, c));
	if (tetr == 5)
		return (canplace5(to_fill, i, j, c));
	if (tetr == 6)
		return (canplace6(to_fill, i, j, c));
	if (tetr == 7)
		return (canplace7(to_fill, i, j, c));
	if (tetr == 8)
		return (canplace8(to_fill, i, j, c));
	if (tetr == 9)
		return (canplace9(to_fill, i, j, c));
	return (0);
}

static int		solve_cord2(int to_fill[][32], int tetr, int i, int j)
{
	int	c;

	c = get_letter(to_fill);
	if (tetr == 10)
		return (canplace10(to_fill, i, j, c));
	if (tetr == 11)
		return (canplace11(to_fill, i, j, c));
	if (tetr == 12)
		return (canplace12(to_fill, i, j, c));
	if (tetr == 13)
		return (canplace13(to_fill, i, j, c));
	if (tetr == 14)
		return (canplace14(to_fill, i, j, c));
	if (tetr == 15)
		return (canplace15(to_fill, i, j, c));
	if (tetr == 16)
		return (canplace16(to_fill, i, j, c));
	if (tetr == 17)
		return (canplace17(to_fill, i, j, c));
	if (tetr == 18)
		return (canplace18(to_fill, i, j, c));
	if (tetr == 19)
		return (canplace19(to_fill, i, j, c));
	return (0);
}

int				call_canplace(int tetr, int to_fill[][32], int i, int j)
{
	if (tetr < 10)
		return (solve_cord(to_fill, tetr, i, j));
	else
		return (solve_cord2(to_fill, tetr, i, j));
}
