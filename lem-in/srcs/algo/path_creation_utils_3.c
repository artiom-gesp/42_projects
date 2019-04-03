/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_creation_utils_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:49:37 by agesp             #+#    #+#             */
/*   Updated: 2019/04/02 13:13:51 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		reset_tab(t_lemin *e)
{
	int i;

	i = -1;
	while (++i < e->nb_rooms - 1)
	{
		e->stack[i] = -1;
		e->visited[i] = e->find_new[i];
		e->prev[i] = 0;
	}
	e->visited[i] = e->find_new[i];
	e->visited[e->start->id_r] = 1;
}

void		reset_map_tab(t_lemin *e)
{
	int i;

	i = -1;
	while (++i < e->nb_rooms - 1)
	{
		e->map_stack[i] = -1;
		e->map_visited[i] = 0;
		e->map_prev[i] = 0;
	}
	e->map_visited[i] = 0;
	e->map_visited[e->start->id_r] = 1;
}

void		create_single(t_lemin *e)
{
	if (e->map[e->start->id_r][e->end->id_r] == 1)
	{
		if (!(e->p->path = malloc(sizeof(int) * 2)))
			exit(-1);
		e->p->path[0] = e->start->id_r;
		e->p->path[1] = e->end->id_r;
		e->p->next = NULL;
		e->p->size_path = 2;
	}
}

void		tricky_case(t_lemin *e, int x)
{
	int i;
	int s_y;

	i = -1;
	if (e->map_fn[e->y] == 1 && e->map[e->y][e->x] == -1)
		push_stack(e, x);
	else if (e->map_fn[e->y] == 1 && e->map[e->y][e->x] == 1)
	{
		while (++i < e->nb_rooms)
			if (e->map[i][e->y] == -1)
				break ;
		if (i != e->nb_rooms && !e->map_prev[e->y] && !e->map_prev[i]
				&& i != e->start->id_r)
		{
			s_y = e->y + 1;
			e->map_prev[e->y] = e->x;
			e->y = i;
			push_stack(e, x);
			e->map_prev[i] = s_y - 1;
			e->y = s_y;
		}
	}
}

void		control_stack(t_lemin *e, int x)
{
	e->y = -1;
	if (x == -1)
	{
		while (++e->y < e->nb_rooms)
			if (e->map[e->x][e->y] == x && !e->visited[e->y])
				push_stack(e, x);
		e->x = e->stack[0];
	}
	else
	{
		while (++e->y < e->nb_rooms)
		{
			if (e->map[e->x][e->y] == x && !e->map_visited[e->y])
			{
				if (!e->map_fn[e->y])
					push_stack(e, x);
				else
					tricky_case(e, x);
			}
		}
		e->x = e->map_stack[0];
	}
}
