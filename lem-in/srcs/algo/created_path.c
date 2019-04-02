/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   created_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:59:44 by agesp             #+#    #+#             */
/*   Updated: 2019/04/02 12:05:02 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include <stdio.h>

void		set_map(t_lemin *e)
{
	int save;

	save = e->nb_end;
	while (e->map_prev[save] != e->nb_start)
	{
		if (e->map[save][e->map_prev[save]] == -1)
		{
			e->map[save][e->map_prev[save]] = 1;
			e->map[e->map_prev[save]][save] = 1;
		}
		else
			e->map[e->map_prev[save]][save] = -1;
		save = e->map_prev[save];
		e->map_fn[save] = 1;
	}
	e->map[e->nb_start][save] = -1;
	e->map_fn[e->nb_start] = 1;
}

int			still_paths(t_lemin *e)
{
	int i;

	i = 0;
	while (i < e->nb_rooms)
	{
		if (e->map[e->nb_start][i] == -1 && !e->find_new[i])
			return (1);
		i++;
	}
	return (0);
}

void		bfs(t_lemin *e)
{
	t_path *save;

	save = e->p;
	while (still_paths(e))
	{
		e->x = e->nb_start;
		reset_tab(e);
		while (e->x != e->nb_end)
		{
			control_stack(e, -1);
			if (e->x == e->nb_end || is_stack_empty(e->stack, e->nb_rooms - 1))
				break ;
			e->visited[e->x] = 1;
			pop_stack(e, e->nb_rooms, -1);
		}
		if (is_stack_empty(e->stack, e->nb_rooms - 1))
			break ;
		e->find_new[add_path(e)] = 1;
	}
	e->p = save;
	e->p->steps = get_len(e);
	ft_printf("len %d\n", get_len(e));
}

int			copy_path(t_lemin *e)
{
	t_path *save;

	save = NULL;
	if (e->p && e->p->steps == -1)
	{
		free_path(e->p, 0);
		return (1);
	}
	if (!e->select_p || (e->select_p && e->select_p->steps > e->p->steps))
	{
		if (e->select_p)
			e->select_p = free_path(e->select_p, 0);
		e->select_p = e->p;
		e->p = NULL;
		e->p = free_path(e->p, 1);
	}
	else
		e->p = free_path(e->p, 1);
	return (0);
}

void		setup_map(t_lemin *e)
{
	set_bfs_base_var(e);
	create_single(e);
	while (paths_remain(e) && e->map[e->nb_start][e->nb_end] == 0)
	{
		e->x = e->nb_start;
		reset_map_tab(e);
		while (e->x != e->nb_end)
		{
			control_stack(e, 1);
			if (e->x == e->nb_end
					|| is_stack_empty(e->map_stack, e->nb_rooms - 1))
				break ;
			e->map_visited[e->x] = 1;
			pop_stack(e, e->nb_rooms, 1);
		}
		if (is_stack_empty(e->map_stack, e->nb_rooms - 1))
			break ;
		set_map(e);
		bfs(e);
		if (copy_path(e))
			break ;
		ft_bzero(e->find_new, e->nb_rooms * sizeof(int));
	}
	e->p = e->select_p;
}
