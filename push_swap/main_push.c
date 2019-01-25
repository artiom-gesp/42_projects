/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 17:58:07 by agesp             #+#    #+#             */
/*   Updated: 2019/01/25 15:51:20 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int	is_solo(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i])
		return (0);
	return (1);
}

static char	**get_solo(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-' && str[i + 1] && ft_isdigit(str[i + 1]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (NULL);
		i++;
	}
	return (ft_strsplit(str, ' '));
}

static char	**create_tab_2(int ac, char **av)
{
	char	**tab;
	char	*save;

	if (ac == 2 && is_solo(av[1]))
		return (get_solo(av[1]));
	if (ac == 2 && ft_strcmp(av[1], "-v"))
	{
		save = ft_itoa(ft_atoi(av[1]));
		if (ft_strcmp(av[1], save))
			tab = ft_strsplit(av[1], ' ');
		else
			tab = NULL;
		save ? free(save) : do_nothing();
	}
	else
		tab = NULL;
	return (tab);
}

int		main(int ac, char **av)
{
	t_push	*a;
	t_push	*b;
	char	**tab;
	int		save_ac;

	save_ac = ac;
	tab = create_tab_2(ac, av);
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
