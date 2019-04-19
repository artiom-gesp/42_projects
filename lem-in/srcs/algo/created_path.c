/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   created_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:59:44 by agesp             #+#    #+#             */
/*   Updated: 2019/04/08 13:18:03 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		set_map(t_lemin *e)
{
	int save;

	save = e->end->id_r;
	while (e->map_prev[save] != e->start->id_r)
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
	e->map[e->start->id_r][save] = -1;
	e->map_fn[e->start->id_r] = 1;
}

void		bfs(t_lemin *e)
{
	t_path *save;

	save = e->p;
	while (still_paths(e))
	{
		e->x = e->start->id_r;
		reset_tab(e);
		while (e->x != e->end->id_r)
		{
			control_stack(e, -1);
			if (e->x == e->end->id_r
					|| is_stack_empty(e->stack, e->nb_rooms - 1))
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
}

int			copy_path(t_lemin *e)
{
	t_path *save;

	save = NULL;
	if (e->p && e->p->steps == -1)
	{
		e->p = free_path(e->p, 0, e);
		return (1);
	}
	if (!e->select_p || (e->select_p && e->select_p->steps > e->p->steps))
	{
		if (e->select_p)
			e->select_p = free_path(e->select_p, 0, e);
		e->select_p = e->p;
		e->p = NULL;
		e->p = free_path(e->p, 1, e);
	}
	else
		e->p = free_path(e->p, 1, e);
	return (0);
}

void		clean_setup_exit(t_lemin *e)
{
	if (!e->select_p && !e->p)
		lem_in_error(e, 13);
	if (e->p && e->map[e->start->id_r][e->end->id_r] == 0)
		free_path(e->p, 0, e);
	if (e->map[e->start->id_r][e->end->id_r] == 0)
		e->p = e->select_p;
}

void		setup_map(t_lemin *e)
{
	set_bfs_base_var(e);
	create_single(e);
	while (paths_remain(e) && e->map[e->start->id_r][e->end->id_r] == 0)
	{
		e->x = e->start->id_r;
		reset_map_tab(e);
		while (e->x != e->end->id_r)
		{
			control_stack(e, 1);
			if (e->x == e->end->id_r
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
	clean_setup_exit(e);
}
