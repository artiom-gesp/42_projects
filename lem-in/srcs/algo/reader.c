/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:59:44 by kecosmon          #+#    #+#             */
/*   Updated: 2019/03/18 10:46:33 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lemin.h"

static void		verif_start_end(t_lemin *e, enum pos *d)
{
	char	*line;

	while (get_next_line(0, &line) > 0)
	{
		if (line[0] != '#')
			break ;
		ft_strdel(&line);
	}
	if (line[0] == 'L')
		lem_in_error(e, 6);
	rooms(line, e, d);
	ft_strdel(&line);
}

static void		parsing_glob(t_lemin *e, char *line, enum pos *d, int n)
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
		parsing_links(line, e);
}

void			reader(t_lemin *e)
{
	char		*line;
	enum pos	d;

	d = ANTS;
	e->nb_rooms = 0;
	while (get_next_line(0, &line) > 0)
	{
		add_info(e, line);
		parsing_glob(e, line, &d, 0);
		ft_strdel(&line);
	}
	links_rooms(e);
	if (!e->end || !e->start)
		exit(-1);
}
