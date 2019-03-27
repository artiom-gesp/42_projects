/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:58:43 by agesp             #+#    #+#             */
/*   Updated: 2019/03/22 16:04:12 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
/*
int		used_check(t_path *p, t_path *p1)
{*/

int		mini_compare(t_path *p, int nb_paths)
{
	int i;
	int j;
	t_path *save;
	t_path *next;

	while (p && !p->s_conti)
		p = p->next;
	save = p;
	next = p->next;
	while (next && !next->s_conti)
		next = next->next;
	if (!next || !p)
		return (0);
	while (next)
	{
		i = 1;
		while (i < p->size_path - 1)
		{
			j = 1;
			while (j < next->size_path - 1)
			{
				if (p->path[i] == next->path[j])
				{
					next->s_conti = 0;
					nb_paths--;
					break ;
				}
				j++;
			}
			if (j != next->size_path - 1)
				break ;
			i++;
		}
		p = p->next;
		while (p && !p->s_conti)
			p = p->next;
		if (!p)
			p = save;
		next = next->next;
		while (next && !next->s_conti)
			next = next->next;
		if (!next)
			break ;
	}
	return (nb_paths);
}

int		compare_paths(t_path *p, t_path *p1)
{
	int i;
	int j;
	int nb_ok_paths;
	int	nb_paths;
	t_path *save;

	nb_paths = 0;
	save = p;
	nb_ok_paths = 0;
	while (p != p1)
	{
		i = 1;
		while (i < p->size_path - 1)
		{
			j = 1;
			while (j < p1->size_path - 1)
			{
				if (p->path[i] == p1->path[j])
				{
					p->s_conti = 0;
					break ;
				}
				p->s_conti = 1;
				j++;
			}
			if (j != p1->size_path - 1)
				break ;
			i++;
		}
		if (i == p->size_path - 1)
			nb_ok_paths++;
		nb_paths++;
		p = p->next;
	}
	return (nb_ok_paths == nb_paths ? -1 : mini_compare(save, nb_ok_paths));
}

void	reset_s_conti(t_path *p)
{
	while (p)
	{
		p->s_conti = 0;
		if (!p->next)
			break ;
		p = p->next;
	}
}

void	cpy_new_path(t_lemin *e, t_path *p)
{
	t_path	*save;

	save = e->p;
	while (save && save != p)
	{
		save->conti = save->s_conti;
		if (!save->next)
			break ;
		save = save->next;
	}
}

void	select_paths(t_lemin *e)
{
	t_path	*save;
	int		nb_paths;
	int		new_nb_paths;

	save = e->p;
	while (save)
	{
		save->conti = 0;
		if (!save->next)
			break ;
		save = save->next;
	}
	save = e->p;
	save->conti = 1;
	nb_paths = 1;
	save = save->next;
	while (save)
	{
		if ((new_nb_paths = compare_paths(e->p, save)) == -1)
		{
			save->conti = 1;
			save->s_conti = 0;
			nb_paths++;
		}
		else if (new_nb_paths != 0)
		{
			if (new_nb_paths > nb_paths)
			{
				nb_paths = new_nb_paths;
				save->conti = 1;
				cpy_new_path(e, save);
				reset_s_conti(e->p);
			}
			else
				save->conti = 0;
		}
		else
			save->conti = 0;
		if (!save->next)
			break ;
		save = save->next;
	}
}
