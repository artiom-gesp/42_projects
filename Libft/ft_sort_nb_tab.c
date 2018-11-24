/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:08:18 by agesp             #+#    #+#             */
/*   Updated: 2018/11/23 13:11:59 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_sort_nb_tab(int *tab, size_t size)
{
	size_t	i;
	size_t	j;
	int		save;

	i = 0;
	save = 0;
	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			if (tab[i] > tab[j])
			{
				save = tab[i];
				tab[i] = tab[j];
				tab[j] = save;
			}
			i++;
		}
		j++;
	}
	return (tab);
}
