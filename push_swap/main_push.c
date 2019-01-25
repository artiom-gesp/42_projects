/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 17:58:07 by agesp             #+#    #+#             */
/*   Updated: 2019/01/25 11:12:49 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		main(int ac, char **av)
{
	t_push	*a;
	t_push	*b;
	char	**tab;
	int		save_ac;

	save_ac = ac;
	tab = create_tab(ac, av);
	if (tab)
		ac = len_tab(tab);
	if (ac > 1)
	{
		if ((save_ac == ac && is_input_ok((int)ac, av))
				|| (tab && is_input_ok(ac, tab)))
		{
			a = fill_pile(ac, tab ? tab : av, 1);
			b = fill_pile(ac, tab ? tab : av, 0);
			nquick_sort(a, b);
			free_list(a);
			free_list(b);
		}
		else
			ft_printf("Error\n");
		tab ? free_tab(tab) : do_nothing();
	}
	return (0);
}
