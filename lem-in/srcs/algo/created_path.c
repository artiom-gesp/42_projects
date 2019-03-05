/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:59:44 by agesp             #+#    #+#             */
/*   Updated: 2019/03/05 17:13:31 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"
#include <stdio.h>

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

void		push_stack(int *stack, int room, int nb_rooms, int *prev, int x)
{
	int i;

	i = 0;
	while (stack[i] != -1 && i < nb_rooms - 1)
	{
		if (stack[i] == room)
			return ;
		i++;
	}
	prev[room] = x;
	stack[i] = room;
}	

int		print_path(int *prev, t_lemin *e)
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
		next_path = i > 0 && next_path == -1 ? path[i] : -1;
		i++;
	}
	printf("\n\n%s->", e->table_r[e->nb_start]->name);
	while (--i >= 0)
	{
		printf("%s->", e->table_r[path[i]]->name);
	}
	printf("%s\n", e->table_r[e->nb_end]->name);
	return (next_path == -1 ? path[0] : next_path);
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

void		reset_tab(int *stack, int *visited, int *prev, t_lemin *e, int *s)
{
	int i;

	i = -1;
	while (++i < e->nb_rooms - 1)
	{
		stack[i] = -1;
		visited[i] = s[i];
		prev[i] = 0;
	}
	visited[i] = s[i];
}

int			paths_remain(t_lemin *e, int *find_new)
{
	int i;

	i = 0;
	while (i < e->nb_rooms)
	{
		if (e->map[e->nb_start][i] == 1 && !find_new[i])
			return (1);
		i++;
	}
	return (0);
}

void		bfs(t_lemin *e)
{
	int x;
	int y;
	int stack[e->nb_rooms - 1];
	int	visited[e->nb_rooms];
	int prev[e->nb_rooms - 1];
	int	find_new[e->nb_rooms];
	int i;

	i = -1;
	while (++i < e->nb_rooms)
		find_new[i] = 0;
	while (paths_remain(e, find_new))
	{
		x = e->nb_start;
		reset_tab(stack, visited, prev, e, find_new);
		visited[x] = 1;
		while (x != e->nb_end)
		{
			y = 0;
			while (y < e->nb_rooms)
			{
				if (e->map[x][y] == 1 && !visited[y])
					push_stack(stack, y, e->nb_rooms, prev, x);
				y++;
			}
	//		printf("\n\n");
			i = -1;
			while (++i < e->nb_rooms - 1)
	//			printf("%d ", stack[i]);
			x = stack[0];
			if (x == e->nb_end)
				break ;
			visited[x] = 1;
			pop_stack(stack, e->nb_rooms);
		}
		sleep(1);
		printf("to_block %d\n",print_path(prev, e));
		find_new[print_path(prev, e)] = 1;

	}
}
