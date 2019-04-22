/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 11:17:33 by agesp             #+#    #+#             */
/*   Updated: 2018/12/10 17:12:13 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	ft_error(int ac, char *av)
{
	if (ac != 2)
	{
		ft_putstr("usage: ./fillit input_file\n");
		return (0);
	}
	if (av[0] == '\0')
	{
		ft_putstr("error\n");
		return (0);
	}
	return (1);
}

int			main(int ac, char **av)
{
	int			i;
	char		**tab;
	int			to_fill[32][32];
	int			get_tetr[26];

	i = -1;
	while (++i < 26)
		get_tetr[i] = 0;
	if (ft_error(ac, av[1]))
	{
		if (!(tab = make_tab(av[1])))
		{
			ft_putstr("error\n");
			return (0);
		}
		extr_tetr(tab, get_tetr);
		free_tab(tab);
		create_int_tab(to_fill, 2);
		i = ft_solve(get_tetr, to_fill, 0, 0);
		print_result(to_fill, i);
	}
	return (0);
}
