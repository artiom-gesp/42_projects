//  /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   created_path.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/03/04 12:59:44 by agesp             #+#    #+#             */
// /*   Updated: 2019/03/21 14:24:19 by agesp            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "lemin.h"

// int 	one_path(t_lemin *e)
// {
// 	if (!(e->p = ft_memalloc(sizeof(t_lemin))))
// 		lem_in_error(e , 1);
// 	e->p[0].size_path = 1;
// 	e->p[0].r = e->start;
// 	e->p[0].r->next = e->end;
// 	return (1);
// }

// int 	updated(t_lemin *e, t_rooms *cur)
// {
// 	int i;
// 	t_rooms *r;

// 	r = NULL;
// 	i = -1;
// 	while (++i < cur->nb_links)
// 	{
// 		r = cur->links[i];
// 		if (r->dist > cur->dist && cur->status != 3)
// 		{
// 			r->dist = cur->dist + 1;
// 			if (cur->status == 0 && cur != e->end)
// 				cur->status = 1;
// 			else
// 				cur->status = 3;
// 		}
// 	}
// 	return (0);
// }
// void 		updated_path(t_lemin *e)
// {
// 	t_rooms *r;
// 	t_rooms *tmp;
// 	int 	i;

// 	tmp = NULL;
// 	r = e->end;
// 	while (r != e->start)
// 	{
// 		i = 0;
// 		while (r->dist - 1 != r->links[i]->dist)
// 		 	i++;
// 		r->links[i]->r_p = r;
// 		r = r->links[i];
// 	}
// }

// t_rooms 	*bfs(t_lemin *e)
// {
// 	t_rooms *cur;
// 	t_rooms *tmp;
// 	int 	dist;

// 	e->start->dist = 0;
// 	e->start->status = 0;
// 	cur = e->start;
// 	tmp = NULL;
// 	// ft_putendl(e->table_r[6]->name);
// 	// ft_putnbr(e->table_r[6]->status);
// 	while (cur != e->end)
// 	{
// 		dist = INT_MAX;
// 		cur = e->r;
// 		while (cur != NULL)
// 		{
// 			if (cur->dist < dist && cur->status < 2 )
// 			{
// 				dist = cur->dist;
// 				cur->status = 1;
// 				tmp = cur;
// 			}
// 			cur = cur->next;
// 		}
// 		cur = tmp;
// 		updated(e, cur);
// 	}
// 	updated_path(e);
// 	return (e->start);
// }

// void	edmonds_karps(t_lemin *e)
// {
// 	int i;
// 	int dist;

// 	dist = 0;
// 	i = 0;
// 	while (i < e->nb_ants)
// 	{
// 		if (!(e->p[i].r = bfs(e)))
// 			return ;
// 		while (e->p[i].r)
// 		{
// 			ft_putendl(e->p[i].r->name);
// 			e->p[i].r = e->p[i].r->r_p;
// 		}
// 		i++;
// 	}
// }

// int		bfs_edmonds_karps(t_lemin *e)
// {
// 	if (e->mat[e->start->id_r][e->end->id_r])
// 		return (one_path(e));
// 	if (!(e->p = ft_memalloc(sizeof(t_path) * e->start->nb_links + 1)))
// 		lem_in_error(e , 1);
// 	edmonds_karps(e);
// 	return (e->nb_paths);
// }
