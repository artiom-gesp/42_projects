/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_creation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:41:53 by agesp             #+#    #+#             */
/*   Updated: 2019/04/03 09:56:08 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		pop_stack(t_lemin *e, int nb_rooms, int flag)
{
	int i;

	i = 1;
	if (flag == -1)
	{
		while (i < nb_rooms - 1)
		{
			e->stack[i - 1] = e->stack[i];
			i++;
		}
		e->stack[i - 1] = -1;
	}
	else
	{
		while (i < nb_rooms - 1)
		{
			e->map_stack[i - 1] = e->map_stack[i];
			i++;
		}
		e->map_stack[i - 1] = -1;
	}
}

void		push_stack(t_lemin *e, int flag)
{
	int i;

	i = 0;
	if (flag == -1)
	{
		while (e->stack[i] != -1 && i < e->nb_rooms - 1)
		{
			if (e->stack[i] == e->y)
				return ;
			i++;
		}
		e->prev[e->y] = e->x;
		e->stack[i] = e->y;
	}
	else
	{
		while (e->map_stack[i] != -1 && i < e->nb_rooms - 1)
		{
			if (e->map_stack[i] == e->y)
				return ;
			i++;
		}
		e->map_prev[e->y] = e->x;
		e->map_stack[i] = e->y;
	}
}

void		create_path(t_lemin *e, int *pa, int len)
{
	int j;

	j = 1;
	if (e->p->path)
	{
		if (!(e->p->next = malloc(sizeof(t_path))))
			lem_in_error(e, 1);
		e->p = e->p->next;
	}
	if (!(e->p->path = malloc(sizeof(int) * (len + 2))))
		lem_in_error(e, 1);
	e->p->next = NULL;
	e->p->size_path = len + 2;
	while (--len >= 0)
		e->p->path[j++] = pa[len];
	e->p->path[e->p->size_path - 1] = e->end->id_r;
	e->p->path[0] = e->start->id_r;
	e->nb_paths++;
}

int			get_nb_links(t_lemin *e, int x)
{
	int i;
	int links;

	i = 0;
	links = 0;
	while (i < e->nb_rooms)
	{
		if (e->map[x][i] == 1)
			links++;
		i++;
	}
	return (links);
}

int			add_path(t_lemin *e)
{
	int i;
	int save;
	int	*path;
	int	next_path;

	i = 0;
	if (!(path = malloc(sizeof(int) * e->nb_rooms)))
		lem_in_error(e, 1);
	save = e->end->id_r;
	next_path = -1;
	while (e->prev[save] != e->start->id_r)
	{
		path[i] = e->prev[save];
		save = e->prev[save];
		next_path = next_path == -1 && get_nb_links(e, path[i])
			> 2 ? path[i] : -1;
		i++;
	}
	save = i;
	while (i < e->nb_rooms)
		path[i++] = 0;
	create_path(e, path, save);
	free(path);
	e->find_new[e->p->path[1]] = 1;
	return (e->p->path[e->p->size_path - 2]);
}
