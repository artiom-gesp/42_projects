/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 17:58:07 by agesp             #+#    #+#             */
/*   Updated: 2019/01/14 13:15:37 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		main(int ac, char **av)
{
	int i;
	t_push *a;
	t_push *b;
	int		flag;
	char 	**tab;
	int		save_ac;

	i = -1;
	save_ac = ac;
	flag = 0;
	tab = NULL;
	if (ac == 3 && !ft_strcmp(av[1], "-v"))
	{
		tab = ft_strsplit(av[2], ' ');
		ac = len_tab(tab);
	}
	else if (ac == 2 && ft_strcmp(av[1], "-v"))
	{
		tab = ft_strsplit(av[1], ' ');
		ac = len_tab(tab);
	}
	if (ac > 1)
	{
		if ((save_ac == ac && is_input_ok((int)ac, av)) || (tab && is_input_ok(ac, tab)))
		{
			a = fill_pile(ac, tab ? tab : av, 1);
			b = fill_pile(ac, tab ? tab : av, 0);
			if (!ft_strcmp(av[1], "-v"))
				flag = 1;
			//get_mediane(a, b);
			quick_sort(a, b);
		}
	}
}
