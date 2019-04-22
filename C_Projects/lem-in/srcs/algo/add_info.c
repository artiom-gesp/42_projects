/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:59:44 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/04 11:26:57 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static t_info	*new_info(t_lemin *e)
{
	t_info	*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_info))))
		lem_in_error(e, 1);
	return (tmp);
}

void			add_info(t_lemin *e, char *line)
{
	t_info	*tmp;

	if (!e->i)
	{
		e->i = new_info(e);
		if (!(e->i->line = ft_strdup(line)))
			lem_in_error(e, 1);
		e->i->next = NULL;
	}
	else
	{
		tmp = e->i;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_info(e);
		if (!(tmp->next->line = ft_strdup(line)))
			lem_in_error(e, 1);
		tmp->next->next = NULL;
	}
}
