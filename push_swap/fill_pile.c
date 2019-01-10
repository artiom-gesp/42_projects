/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 10:41:21 by agesp             #+#    #+#             */
/*   Updated: 2019/01/10 13:59:33 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_push	*fill_pile(int ac, char **av, int is_data)
{
	int		i;
	t_push	*a;

	i = ft_atoi(av[0]) && av[0][0] != '0' ? 0 : 1;
	if (!ft_strcmp(av[1], "-v"))
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
	a = get_start_list(a);
	return (a);
}
