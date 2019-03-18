/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:59:44 by agesp             #+#    #+#             */
/*   Updated: 2019/03/11 11:27:35 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include <stdio.h>

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
	e->visited[e->nb_start] = 1;
}

int			paths_remain(t_lemin *e)
{
	int i;

	i = 0;
	while (i < e->nb_rooms)
	{
		if (e->map[e->nb_start][i] == 1 && !e->find_new[i])
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
	e->stack = malloc(sizeof(int) * e->nb_rooms - 1);
	e->visited = malloc(sizeof(int) * e->nb_rooms);
	e->prev = malloc(sizeof(int) * e->nb_rooms - 1);
	e->find_new = malloc(sizeof(int) * e->nb_rooms);
	if (!e->stack || !e->visited || !e->prev || !e->find_new)
		return ;
	if (!(e->p = malloc(sizeof(t_path))))
		return ;
	e->p->path = NULL;
	e->p->next = NULL;
	while (++i < e->nb_rooms)
		e->find_new[i] = 0;
}

void		print_paths(t_lemin *e, t_path *sa)
{
	int i;

	e->p = sa;
	while (e->p)
	{
		ft_printf("\npath_len : %d\n", e->p->size_path);
		i = -1;
		while (++i < e->p->size_path - 1)
			ft_printf("%d->", e->p->path[i]);
		ft_printf("%d\n", e->p->path[e->p->size_path - 1]);
		i = -1;
		while (++i < e->p->size_path - 1)
			ft_printf("%s->", e->table_r[e->p->path[i]]->name);
		ft_printf("%s\n\n", e->table_r[e->p->path[e->p->size_path - 1]]->name);
		if (!e->p->next)
			break ;
		e->p = e->p->next;
	}
}

void		discover_more_paths(t_lemin *e, t_path *s)
{
	int		i;
	t_path	*save;
	int		get_path;
	int		j;

	i = -1;
	get_path = -1;
	save = s;
	while (++i < e->p->size_path - 1)
		if (e->find_new[get_path = e->p->path[i]] == 1)
		{
			while (save)
			{
				j = -1;
				if (save->next && save == e->p)
					save = save->next;
				if (!save->next && save == e->p)
					break ;
				while (++j < save->size_path - 1)
					if (save->path[j] == get_path)
						while (++j < save->size_path - 1)
							e->find_new[save->path[j]] = 0;
				save = save->next;
			}
		}
}

void		bfs(t_lemin *e)
{
	t_path *save;

	set_bfs_base_var(e);
	save = e->p;
	while (paths_remain(e))
	{
		if (e->map[e->nb_start][e->nb_end] == 1)
		{
			add_path(e);
			break ;
		}
		e->x = e->nb_start;
		reset_tab(e);
		while (e->x != e->nb_end)
		{
			e->y = 0;
			while (e->y < e->nb_rooms)
			{
				if (e->map[e->x][e->y] == 1 && !e->visited[e->y])
					push_stack(e);
				e->y++;
			}
			e->x = e->stack[0];
			if (e->x == e->nb_end || is_stack_empty(e->stack, e->nb_rooms - 1))
				break ;
			e->visited[e->x] = 1;
			pop_stack(e, e->nb_rooms);
		}
		if (is_stack_empty(e->stack, e->nb_rooms - 1))
			break ;
		e->find_new[add_path(e)] = 1;
		discover_more_paths(e, save);
		if (e->p->size_path == 5)
			ft_printf("jj %d\n", e->p->path[3]);
	}
	print_paths(e, save);
	e->p = save;
}
