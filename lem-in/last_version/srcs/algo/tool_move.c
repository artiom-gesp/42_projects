/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:31:29 by kecosmon          #+#    #+#             */
/*   Updated: 2019/03/12 16:56:08 by kecosmon 	      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int 	set(t_path *p, int **map, int c)
{
	int i;

	i = -1;
	while (++i + 1 < p->size_path)
		map[p->path[i]][p->path[i]] = c;
	return (i + 1);
}

int 	condition(t_path *p, t_path *ok, int **map, int count)
{
	if (p->stop == 2)
	{
		set(ok, map, 4);
		set(p, map, 0);
		p->stop = 4;
		p->conti = 0;
		return (0);
	}
	else 
	{
		ok->conti = 0;
		ok->stop = 4;
		p->stop = 0;
		p->conti = 1;
		return (count);
	}
}

void 	zero_vistid(t_lemin *e)
{
	t_path *p;
	int i;

	p = e->p;
	while (p)
	{
		i = -1;
		while (++i < p->size_path)
			e->table_r[p->path[i]]->occuped = 0;
		p = p->next;
	}
}

void 	free_path(t_path **p)
{
	t_path *to_free;

	if (*p)
	{	
		if ((*p)->conti == 0)
		{
			to_free = *p;
			*p = (*p)->next;
			free(to_free);
			free_path(p);
		}
		else
			free_path(&(*p)->next);
	}
}
