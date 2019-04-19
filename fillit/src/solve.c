/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 15:08:15 by agesp             #+#    #+#             */
/*   Updated: 2018/12/10 13:21:39 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		init_var_rft(int *i, int *j, int *flag, int *save)
{
	*i = -1;
	*j = 0;
	*flag = 0;
	*save = 0;
}

static int		remove_from_tab(int tab[][32], int letter, int *save_j)
{
	int i;
	int j;
	int flag;
	int save;

	init_var_rft(&i, &j, &flag, &save);
	while (tab[++i][0] != -1 && i < 32)
	{
		j = 0;
		while (tab[i][j] != -1 && j < 32)
		{
			if (tab[i][j] == letter)
			{
				if (flag == 0)
				{
					save = i;
					flag = 1;
					*save_j = j;
				}
				tab[i][j] = 0;
			}
			j++;
		}
	}
	return (save);
}

static void		reset_and_inc(int *inc, int *i, int *j)
{
	*inc = *inc + 1;
	*i = 0;
	*j = 0;
}

int				ft_solve(int tetr[], int tab[][32], int i, int j)
{
	int size;
	int nb;

	size = 2;
	nb = 0;
	while (tetr[nb] != 0)
	{
		if (call_canplace(tetr[nb], tab, i, j))
			reset_and_inc(&nb, &i, &j);
		else if (nb - 1 >= 0 && tetr[nb - 1])
		{
			nb--;
			i = remove_from_tab(tab, nb + 1, &j);
			j++;
		}
		else
		{
			reset_and_inc(&size, &i, &j);
			create_int_tab(tab, size);
			nb = 0;
		}
	}
	return (size);
}
