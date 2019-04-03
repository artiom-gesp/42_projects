/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:59:44 by kecosmon          #+#    #+#             */
/*   Updated: 2019/03/18 10:46:33 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"


static void			add_start(t_rooms *r, t_lemin *e, enum pos *d)
{
	if (!e->start && *d == START)
		e->start = r;
	else if (!e->end && *d == END)
		e->end = r->next;
	else
		lem_in_error(e, 7);
}

static void			add_rooms(t_rooms **tmp, t_lemin *e, char *line, int i, enum pos *d)
{
	if (!e->r)
	{
		e->r = new_rooms(e);
		e->r->name = name_rooms(e, line, ' ');
		e->nb_rooms++;
		(*tmp) = e->r;	
		e->r->next = NULL;
	}
	else
	{
		while ((*tmp)->next != NULL && i++)
			(*tmp) = (*tmp)->next;
		(*tmp)->next = new_rooms(e);
		(*tmp)->next->id_r = i;
		e->nb_rooms++;
		(*tmp)->next->dist = INT_MAX;
		(*tmp)->next->name = name_rooms(e, line, ' ');
		(*tmp)->next->next = NULL;
	}
	if (*d == START || *d == END)
		add_start(*tmp, e, d);
}

void				rooms(char *line, t_lemin *e, enum pos *d)
{
	int		i;
	t_rooms *r;

	r = e->r;
	if ((i = ft_strichr(line, ' ')))
		parsing_rooms(e, line, i++);
	else	
	{
		*d = LINKS;
		created_hastable(e);
		e->table_r = table_rooms(e);
		parsing_links(line, e);
		return ;
	}
	if (line[0] == 'L')
		lem_in_error(e, 6);
	add_rooms(&r, e, line, 1, d);
	*d = ROOMS;
}
