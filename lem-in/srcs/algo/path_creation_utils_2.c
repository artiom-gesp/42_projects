/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_creation_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 10:22:02 by agesp             #+#    #+#             */
/*   Updated: 2019/04/04 11:33:39 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			still_paths(t_lemin *e)
{
	int i;

	i = 0;
	while (i < e->nb_rooms)
	{
		if (e->map[e->start->id_r][i] == -1 && !e->find_new[i])
			return (1);
		i++;
	}
	return (0);
}

int			paths_remain(t_lemin *e)
{
	int i;

	i = 0;
	while (i < e->nb_rooms)
	{
		if (e->map[e->start->id_r][i] == 1)
			return (1);
		i++;
	}
	return (0);
}

int			is_stack_empty(int *stack, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (stack[i] != -1)
			return (0);
		i++;
	}
	return (1);
}

void		set_bfs_base_var(t_lemin *e)
{
	int i;

	i = -1;
	e->nb_paths = 0;
	if (!(e->p = malloc(sizeof(t_path))))
		lem_in_error(e, 1);
	e->p->path = NULL;
	e->p->next = NULL;
	e->stack = malloc(sizeof(int) * e->nb_rooms - 1);
	e->map_stack = malloc(sizeof(int) * e->nb_rooms - 1);
	e->visited = malloc(sizeof(int) * e->nb_rooms);
	e->map_visited = malloc(sizeof(int) * e->nb_rooms);
	e->prev = malloc(sizeof(int) * e->nb_rooms);
	e->map_prev = malloc(sizeof(int) * e->nb_rooms);
	e->find_new = malloc(sizeof(int) * e->nb_rooms);
	e->map_fn = malloc(sizeof(int) * e->nb_rooms);
	if (!e->stack || !e->visited || !e->prev || !e->find_new)
		lem_in_error(e, 1);
	if (!e->map_stack || !e->map_visited || !e->map_prev || !e->map_fn)
		lem_in_error(e, 1);
	while (++i < e->nb_rooms)
	{
		e->find_new[i] = 0;
		e->map_fn[i] = 0;
	}
}

void		print_paths(t_lemin *e, t_path *sa)
{
	int i;

	while (sa)
	{
		ft_printf("\npath_len : %d\n", sa->size_path);
		i = -1;
		while (++i < sa->size_path - 1)
			ft_printf("%s->", e->table_r[sa->path[i]]->name);
		ft_printf("%s\n\n", e->table_r[sa->path[sa->size_path - 1]]->name);
		if (!sa->next)
			break ;
		sa = sa->next;
	}
}
