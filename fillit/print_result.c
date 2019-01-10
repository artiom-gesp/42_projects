/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:45:59 by agesp             #+#    #+#             */
/*   Updated: 2018/12/09 14:23:08 by uroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	print_result(int to_fill[][32], int size)
{
	int		i;
	int		j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (to_fill[i][j] == 0)
				ft_putchar('.');
			else
				ft_putchar(to_fill[i][j] + 64);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
