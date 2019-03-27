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

char				*name_rooms(char *line)
{
	int		i;
	char	*str;

	i = 0;
	while (line[i] != ' ' && line[i])
		i++;
	if (!(str = ft_strsub(line, 0, i)))
		exit(-1);
	return (str);
}

static void			add_rooms(t_lemin *e, char *line, int i)
{
	t_rooms	*tmp;

	tmp = e->r;
	if (!e->r)
	{
		e->nb_rooms = 0;
		e->r = new_rooms();
		e->r->name = name_rooms(line);
		e->r->nb_rooms = 0;
		e->nb_rooms++;
		e->r->next = NULL;
	}
	else
	{
		while (tmp->next != NULL)
		{
			i++;
			tmp = tmp->next;
		}
		tmp->next = new_rooms();
		tmp->next->nb_rooms = i;
		e->nb_rooms++;
		tmp->next->name = name_rooms(line);
		tmp->next->next = NULL;
	}
}

static void			add_start(t_lemin *e, char *line)
{
	if (!e->start)
	{
		e->start = new_rooms();
		e->start->name = name_rooms(line);
		e->start->nb_rooms = e->nb_rooms;
	}
	e->st = 0;
}

static void			add_end(t_lemin *e, char *line)
{
	if (!e->end)
	{
		e->end = new_rooms();
		e->end->name = name_rooms(line);
		e->end->nb_rooms = e->nb_rooms;
	}
	e->nd = 0;
}

void				parsing_rooms(char *line, t_lemin *e, enum pos *d)
{
	int		i;

	i = 0;
	while (line[i] != ' ' && line[i])
		i++;
	if (line[0] == 'L')
		exit(-1);
	if (!line[i])
	{
		*d = LINKS;
		parsing_links(line, e);
		return ;
	}
	if (e->st == 1)
		add_start(e, line);
	else if (e->nd == 1)
		add_end(e, line);
	add_rooms(e, line, 1);
	i++;
	coor_room(line, i);
}
