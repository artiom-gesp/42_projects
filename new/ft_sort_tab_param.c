/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_tab_param.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:40:09 by agesp             #+#    #+#             */
/*   Updated: 2018/11/23 12:03:12 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_sort_tab_param(char **tab, int (*f)(const char *, const char *))
{
	int		i;
	char	*save;

	i = 0;
	save = NULL;
	while (tab[i])
	{
		if (tab[i + 1] && f(tab[i], tab[i + 1]) > 0)
		{
			save = tab[i + 1];
			tab[i + 1] = tab[i];
			tab[i] = save;
			i = 0;
		}
		else
			i++;
	}
	return (tab);
}
