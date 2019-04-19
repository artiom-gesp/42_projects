/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:59:44 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/08 16:42:36 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void			add_start(t_rooms *r, t_lemin *e, enum e_pos *d)
{
	if (!e->start && *d == START)
		e->start = r;
	else if (!e->end && *d == END)
		e->end = r->next;
	else
		lem_in_error(e, 7);
}

static void			copy_next_room(t_rooms **tmp, t_lemin *e, char *line, int i)
{
	while ((*tmp)->next != NULL && i++)
		(*tmp) = (*tmp)->next;
	(*tmp)->next = new_rooms(e);
	(*tmp)->next->id_r = i;
	e->nb_rooms++;
	(*tmp)->next->dist = INT_MAX;
	(*tmp)->next->name = name_rooms(e, line, ' ');
	if (ft_strlen((*tmp)->next->name) > 30)
		lem_in_error(e, 19);
	(*tmp)->next->next = NULL;
}

static void			add_rooms(t_lemin *e, char *line, int i, enum e_pos *d)
{
	t_rooms *tmp;

	tmp = e->r;
	if (!e->r)
	{
		e->r = new_rooms(e);
		e->r->name = name_rooms(e, line, ' ');
		if (ft_strlen(e->r->name) > 30)
			lem_in_error(e, 19);
		e->nb_rooms++;
		tmp = e->r;
		e->r->next = NULL;
	}
	else
		copy_next_room(&tmp, e, line, i);
	if (*d == START || *d == END)
		add_start(tmp, e, d);
}

void				rooms(char *line, t_lemin *e, enum e_pos *d)
{
	int		i;

	if ((i = ft_strichr(line, ' ')))
		parsing_rooms(e, line, i++);
	else
	{
		*d = LINKS;
		if (!e->r)
			lem_in_error(e, 11);
		created_hastable(e);
		e->table_r = table_rooms(e);
		parsing_links(line, e);
		return ;
	}
	if (line[0] == 'L')
		lem_in_error(e, 6);
	add_rooms(e, line, 1, d);
	*d = ROOMS;
}
