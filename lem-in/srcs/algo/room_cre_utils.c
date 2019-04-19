/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_cre_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 09:55:09 by agesp             #+#    #+#             */
/*   Updated: 2019/04/05 11:32:41 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_rooms		*new_rooms(t_lemin *e)
{
	t_rooms	*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_rooms))))
		lem_in_error(e, 1);
	return (tmp);
}

static int	duplicate(t_lemin *e, t_rooms *r, char *line)
{
	char *str;

	str = name_rooms(e, &line[0], ' ');
	while (r)
	{
		if ((!ft_strcmp(r->name, str)))
		{
			ft_strdel(&str);
			return (1);
		}
		r = r->next;
	}
	ft_strdel(&str);
	return (0);
}

void		parsing_rooms(t_lemin *e, char *line, int i)
{
	int		x;
	int		y;
	t_rooms	*r;

	r = e->r;
	x = ft_atoii(line, &i);
	y = ft_atoii(line, &i);
	if (line[i])
		lem_in_error(e, 15);
	if (x < 0 || y < 0)
		lem_in_error(e, 15);
	if (duplicate(e, r, line))
		lem_in_error(e, 16);
}

char		*name_rooms(t_lemin *e, char *line, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (line[i] != c && line[i])
		i++;
	if (!(str = ft_strsub(line, 0, i)))
		lem_in_error(e, 1);
	return (str);
}
