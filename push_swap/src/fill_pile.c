/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:41:21 by agesp             #+#    #+#             */
/*   Updated: 2019/01/30 15:58:45 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

t_push	*set_color(t_push *p)
{
	p = get_start_list(p);
	while (p)
	{
		p->color = 0;
		if (!p->next)
			break ;
		p = p->next;
	}
	p = get_start_list(p);
	return (p);
}

t_push	*fill_pile(int ac, char **av, int is_data)
{
	int		i;
	t_push	*a;

	i = av[0][0] == '/' || av[0][0] == '.' ? 1 : 0;
	if (!ft_strcmp(av[1], "-v") || !ft_strcmp(av[1], "-w"))
		i++;
	if (!(a = malloc(sizeof(t_push))))
		return (NULL);
	a->next = NULL;
	a->data = is_data ? atoi(av[i]) : 0;
	a->is_data = is_data;
	a->prev = NULL;
	while (i < ac - 1)
	{
		if (!(a->next = malloc(sizeof(t_push))))
			return (NULL);
		a->next->next = NULL;
		a->next->prev = a;
		a->next->data = is_data ? atoi(av[i + 1]) : 0;
		a->next->is_data = is_data;
		a = a->next;
		i++;
	}
	a = set_color(a);
	return (a);
}
