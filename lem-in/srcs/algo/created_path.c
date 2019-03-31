/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   created_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:59:44 by agesp             #+#    #+#             */
/*   Updated: 2019/03/28 15:37:49 by agesp            ###   ########.fr       */
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
	e->map_visited[e->nb_start] = 1;
}

void		create_single(t_lemin *e)
{
	if (e->map[e->nb_start][e->nb_end] == 1)
	{
		if (!(e->p->path = malloc(sizeof(int) * 2)))
			exit(-1);
		e->p->path[0] = e->nb_start;
		e->p->path[1] = e->nb_end;
		e->p->next = NULL;
		e->p->size_path = 2;
	}
}

void		control_stack(t_lemin *e, int x)
{
	int i;
	int s_y;

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
				{
					i = -1;
					if (e->map_fn[e->y] == 1 && e->map[e->y][e->x] == -1)
						push_stack(e, x);
					else if (e->map_fn[e->y] == 1 && e->map[e->y][e->x] == 1)
					{
						while (++i < e->nb_rooms )
							if (e->map[i][e->y] == -1)
									break ;
						if (i != e->nb_rooms && !e->map_prev[e->y] && !e->map_prev[i] && i != e->nb_start)
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
			}
		}
		e->x = e->map_stack[0];
	}
}

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
}

void		get_nb_lines(t_lemin *e)
{
	t_path *p;
	int		nb_paths;
	int		i;

	p = e->p;
	i = -1;
	nb_paths = 0;
	while (p && ++i < e->nb_ants)
	{
		nb_paths++;
		if (!p->next)
			break ;
		p = p->next;
	}
	i = e->nb_ants / nb_paths;
	i += p->size_path - 2;
	i += e->nb_ants % nb_paths != 0 ? 1 : 0;
	e->p->steps = i;
//		ft_printf("len of longest path : %d\n", p->size_path);
	//	ft_printf("number of paths : %d\n", nb_paths);
	//	ft_printf("number of lines : %d\n", i);
}

t_path		*free_path(t_path *p, int realloc)
{
	t_path	*save;
	while (p)
	{
		save = p;
		p = p->next;
		free(save->path);
		free(save);
	}
	if (realloc)
	{
		p = malloc(sizeof(t_path));
		p->next = NULL;
		p->path = NULL;
		return (p);
	}
	return (NULL);
}

void		copy_path(t_lemin *e)
{
	t_path *save;

	save = NULL;
	if (!e->select_p || (e->select_p && e->select_p->steps > e->p->steps))
	{
		if (e->select_p)
			e->select_p = free_path(e->select_p, 0);
		while (e->p)
		{
			if (!e->select_p)
			{
				if (!(e->select_p = malloc(sizeof(t_path))))
					exit(-1);
				save = e->select_p;
			}
			else
			{
				if (!(e->select_p->next = malloc(sizeof(t_path))))
					exit(-1);
				e->select_p = e->select_p->next;
			}
			if (!(e->select_p->path = malloc(sizeof(int) * e->p->size_path)))
				exit(-1);
			e->select_p->steps = e->p->steps;
			e->select_p->size_path = e->p->size_path;
			ft_intcpy(e->select_p->path, e->p->path, e->p->size_path - 1);
			e->select_p->next = NULL;
			if (!e->p->next)
				break ;
			e->p = e->p->next;
		}
		e->select_p = save;
	}
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
			if (e->x == e->nb_end || is_stack_empty(e->map_stack, e->nb_rooms - 1))
				break ;
			e->map_visited[e->x] = 1;
			pop_stack(e, e->nb_rooms, 1);
		}
		if (is_stack_empty(e->map_stack, e->nb_rooms - 1))
			break ;
		set_map(e);
		bfs(e);
		get_nb_lines(e);
		copy_path(e);
		e->p = free_path(e->p, 1);
		ft_bzero(e->find_new, e->nb_rooms * sizeof(int));
	}
	e->p = free_path(e->p, 0);
	e->p = e->select_p;
}
