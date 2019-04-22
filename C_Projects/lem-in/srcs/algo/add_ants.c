/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:59:44 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/04 11:26:52 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

static t_ants		*new_ants(t_lemin *e)
{
	t_ants	*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_ants))))
		lem_in_error(e, 1);
	return (tmp);
}

static void			add_ants(t_lemin *e, int i)
{
	t_ants	*tmp;

	tmp = e->a;
	if (!e->a)
	{
		e->a = new_ants(e);
		e->a->nb_ants = i;
		e->a->next = NULL;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_ants(e);
		tmp->next->nb_ants = i;
		tmp->next->next = NULL;
	}
}

void				parsing_ants(t_lemin *e, char *line)
{
	int		i;

	i = 0;
	if (line[i] == '+')
		i++;
	else if (line[i] == '-')
	{
		ft_strdel(&line);
		lem_in_error(e, 2);
	}
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != 0)
	{
		ft_strdel(&line);
		lem_in_error(e, 2);
	}
	e->nb_ants = ft_atoi(line);
	i = 0;
	while (++i < e->nb_ants + 1)
		add_ants(e, i);
}
