/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 14:31:37 by agesp             #+#    #+#             */
/*   Updated: 2019/04/03 14:53:42 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		get_max_len(t_path *p)
{
	int max;

	max = 0;
	while (p)
	{
		if ((p->size_path - 2) > max)
			max = (p->size_path - 2);
		if (!p->next)
			break ;
		p = p->next;
	}
	return (max);
}

int		get_total_len(t_path *p)
{
	int total;

	total = 0;
	while (p)
	{
		total += (p->size_path - 2);
		if (!p->next)
			break ;
		p = p->next;
	}
	return (total);
}

int		get_nb_paths(t_path *p)
{
	int nb_paths;

	nb_paths = 0;
	while (p)
	{
		nb_paths++;
		if (!p->next)
			break ;
		p = p->next;
	}
	return (nb_paths);
}

int		get_len(t_lemin *e)
{
	int max;
	int rooms;
	int	nb_paths;
	int ants;

	max = get_max_len(e->p);
	rooms = get_total_len(e->p);
	nb_paths = get_nb_paths(e->p);
	if (nb_paths == 0)
		return (-5);
	ants = ((max * nb_paths) - rooms);
	ants = e->nb_ants - ants;
	if (ants < 0)
		return (-1);
	return (max + (ants / nb_paths) + (ants % nb_paths != 0 ? 1 : 0));
}

void	set_path_capacity(t_lemin *e)
{
	t_path	*p;
	int		ants;
	int		app;

	p = e->p;
	ants = e->nb_ants;
	while (p)
	{
		app = e->max_lines - p->size_path + 2;
		if (ants < app)
			p->capacity = ants;
		else
		{
			p->capacity = app;
			ants -= app;
		}
		if (!p->next)
			break ;
		p = p->next;
	}
	e->nb_paths = get_nb_paths(e->p);
}
