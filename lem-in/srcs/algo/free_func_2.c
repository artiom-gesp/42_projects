/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:36:22 by agesp             #+#    #+#             */
/*   Updated: 2019/04/05 11:21:16 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			free_ants(t_lemin *e)
{
	t_ants *a;

	while (e->a)
	{
		a = e->a;
		e->a = e->a->next;
		if (a->p)
			free_path(a->p, 0, e);
		free(a);
	}
}

void			path_fun_free(t_lemin *e)
{
	if (e->p)
		free_path(e->p, 0, e);
	if (e->find_new)
	{
		free(e->stack);
		free(e->map_stack);
		free(e->find_new);
		free(e->map_fn);
		free(e->prev);
		free(e->map_prev);
		free(e->visited);
		free(e->map_visited);
	}
}

void			free_map1(t_lemin *e)
{
	int i;

	i = -1;
	if (e->map)
	{
		while (++i < e->nb_rooms)
			free(e->map[i]);
		free(e->map);
	}
}

void			zero_ants(t_lemin *e)
{
	t_ants *a;

	a = e->a;
	while (a)
	{
		a->p->i = 1;
		a = a->next;
	}
}
