/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:59:44 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/08 16:42:38 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		verif_start_end(t_lemin *e, enum e_pos *d)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		add_info(e, line);
		if (line[0] != '#')
			break ;
		add_info(e, line);
		ft_strdel(&line);
	}
	if (!line || (line && line[0] == 'L'))
		ft_strdel(&line);
	if (!line)
		lem_in_error(e, 8);
	if (line[0] == 'L')
		lem_in_error(e, 6);
	rooms(line, e, d);
	ft_strdel(&line);
}

static void		parsing_glob(t_lemin *e, char *line, enum e_pos *d, int n)
{
	if (!ft_strcmp(line, "##start") && (*d = START))
		verif_start_end(e, d);
	else if (!ft_strcmp(line, "##end") && (*d = END))
		verif_start_end(e, d);
	else if (line[0] == '#')
		n = 1;
	else if (*d == ANTS && n != 1 && (*d = ROOMS))
		parsing_ants(e, line);
	else if (*d == ROOMS && n != 1)
		rooms(line, e, d);
	else if (*d == LINKS)
		if (parsing_links(line, e))
			e->stop = 1;
}

void			reader(t_lemin *e)
{
	char		*line;
	enum e_pos	d;

	d = ANTS;
	e->nb_rooms = 0;
	while (get_next_line(0, &line) > 0)
	{
		add_info(e, line);
		parsing_glob(e, line, &d, 0);
		ft_strdel(&line);
		if (e->stop == 1)
			break ;
	}
	if (d != LINKS)
		lem_in_error(e, 12);
	links_rooms(e);
	if (!e->end || !e->start)
		lem_in_error(e, 8);
	if (e->nb_ants == 0)
		lem_in_error(e, 3);
}
