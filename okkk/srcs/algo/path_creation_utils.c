/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_creation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:41:53 by agesp             #+#    #+#             */
/*   Updated: 2019/03/07 14:54:46 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		pop_stack(int *stack, int nb_rooms)
{
	int i;

	i = 1;
	while (i < nb_rooms - 1)
	{
		stack[i - 1] = stack[i];
		i++;
	}
	stack[i - 1] = -1;
}	

void		push_stack(int *stack, t_lemin *e, int *prev)
{
	int i;

	i = 0;
	while (stack[i] != -1 && i < e->nb_rooms - 1)
	{
		if (stack[i] == e->y)
			return ;
		i++;
	}
	prev[e->y] = e->x;
	stack[i] = e->y;
}	

void	create_path(t_lemin *e, int *path, int len)
{
	int j;
	static int u = 0;

	j = 1;
	u++;
	if (e->p->path)
	{
		if (!(e->p->next = malloc(sizeof(t_path))))
			return ;
		e->p = e->p->next;
	}
	if (!(e->p->path = malloc(sizeof(int) * len + 2)))
		return ;
	e->p->next = NULL;
	e->p->size_path = len + 2;
	e->p->path[0] = e->nb_start;
	e->p->path[len + 1] = e->nb_end;
	while (--len >= 0)
		e->p->path[j++] = path[len];	
	e->p->path[e->p->size_path - 1] = e->nb_end;
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

int		add_path(int *prev, t_lemin *e)
{
	int i;
	int save;
	int	path[e->nb_rooms];
	int	next_path;

	i = 0;
	save = e->nb_end;
	next_path = -1;
	while (prev[save] != e->nb_start)
	{
		path[i] = prev[save];
		save = prev[save];
		next_path = next_path == -1 && get_nb_links(e, path[i])
			> 2 ? path[i] : -1;
		i++;
	}
	create_path(e, path, i);
	i = next_path == -1 ? path[0] : next_path;
	ft_printf("to_block : %d\n", i);
	return (next_path == -1 ? path[0] : next_path);
}
