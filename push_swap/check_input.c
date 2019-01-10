/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:48:03 by agesp             #+#    #+#             */
/*   Updated: 2019/01/10 11:27:22 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	is_tab_ok(int tab[], int size)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (j == i)
				j++;
			if (j != size && tab[i] == tab[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int			is_input_ok(char ac, char **av)
{
	int 	i;
	int		tab[ac - 1];
	char	*save;

	i = 1;
	save = NULL;
	if (!ft_strcmp(av[1], "-v"))
		i++;
	while (i < ac)
	{
		if (!((tab[i - 1] = ft_atoi(av[i])) && av[i][0] != '0'))
			return (0);
		save = ft_itoa_base(tab[i - 1], 10, 'a');
		if (save[0] != av[i][0])
			return (0);
		i++;
	}
	return (is_tab_ok(tab, ac - 1));
}
