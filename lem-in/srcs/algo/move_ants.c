/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:31:29 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/01 17:05:02 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int 	take_better_path(t_path *p, t_lemin *e, int **map)
{
	t_path 	*tmpp;
	int 	i;
	t_path 	*ok;
	int 	count;
	
	tmpp = e->p;
	while (tmpp)
	{
		i = 0;
		while (++i + 1 < tmpp->size_path)
			if (tmpp->path[i] == p->path[i] && tmpp->conti == 1)
			{
				ok = tmpp;
				count = set(tmpp, map, 0);
				set(p, map, 4);
			}
			else if (tmpp->path[i] == p->path[i] && tmpp->conti == 0 && i + 1  < p->size_path)
			{
				p->stop = 2;
			}
		tmpp = tmpp->next;
	}
	return(condition(p, ok, map, count));
}

void			ft_alloc(t_lemin *e, t_path *p)
{
	t_ants	*tmp;

	tmp = e->a;
	if (!e->a->p)
	{
		e->a->p = malloc(sizeof(t_path));
		e->a->p->i = 1;
		e->a->p->size_path = p->size_path;
		e->a->p->path = malloc(sizeof(int) * p->size_path);
		ft_intcpy(e->a->p->path, p->path, p->size_path - 1);
	}
	else
	{
		while (tmp->p)
		{
			tmp = tmp->next;
		}
		tmp->p = malloc(sizeof(t_path));
		tmp->p->i = 1;
		tmp->p->size_path = p->size_path;
		tmp->p->path = malloc(sizeof(int) * p->size_path);
		ft_intcpy(tmp->p->path, p->path, p->size_path - 1);
	}
}

void 	call_path(t_lemin *e, t_ants **a, t_path *p)
{
	int i;
	int count_ants;
	int count;

	count = 0;
	count_ants = 0;
	i = 0;
	while (++count_ants && ++i + 1 < p->size_path && (*a)->nb_ants)
		if (e->map[p->path[i]][p->path[i]] == 4 && p->conti == 0)
		{
			if (p->stop == 4)
				break ;
			p->conti = 2;
			if (!(count = take_better_path(p, e, e->map)))
				break ;
		}
		else
			e->map[p->path[i]][p->path[i]] = 4;
	count_ants -= count;
	if (i + 1 == p->size_path)
		p->conti = 1;
	if (count_ants > 0)
		while (count_ants)
		{
			if (*a)
				(*a) = (*a)->next;
			count_ants--;
		}
}

void	malloc_move(t_lemin *e, t_path *p)
{
	t_ants *a;
	t_path *save;
	int		i;

	a = e->a;
	i = 0;
	while (p)
	{
//		ft_printf("%d\n", p->capacity);
		i++;
		p = p->next;
	}
//	print_paths(e, e->p);
	p = e->p;
	a = e->a;
	while (a)
	{
		if (a && p->capacity)
		{
			ft_alloc(e, p);
			if (!a->next)
				break ;
			a = a->next;
			save = p->next;
		}
		if (p->capacity > 0)
			p->capacity--;
		if (!p->next)
			p = e->p;
		else
			p = p->next;
	}
}

int		not_all_printed(t_ants *a)
{
	while (a)
	{
		if (a->p->i != a->p->size_path)
			return (1);
		a = a->next;
	}
	return (0);
}

void	move_ants_forward(t_lemin *e)
{
	t_path *p;
	t_ants *a;
	int i;
	// char *tmp;
	i = 0;
	a = e->a;
	p = e->p;
	while (p)
	{
		call_path(e, &a, p);
		if (!a)
			break ;
		if (p->next == NULL && a->next != NULL)
			p = e->p;
		else
			p = p->next;
	}
	p = e->p;
//	free_path(&p);
//	select_paths(e);
	p = e->p;
//	print_paths(e, p);
//	ft_printf("%%\n");
	p = e->p;
	i = 0;
	set_path_capacity(e);
	malloc_move(e, p);
	a = e->a;
	while (a)
	{
		if (a->p->i < a->p->size_path && e->table_r[a->p->path[a->p->i]]->occuped != 2)
		{
			if (a->p->i + 1 == a->p->size_path)
				e->table_r[a->p->path[a->p->i]]->occuped = 0;
			else
				e->table_r[a->p->path[a->p->i]]->occuped = 2;
			// tmp = ft_strjoin(ft_itoa(a->nb_ants), e->table_r[a->p->path[a->p->i]]->name);
			// if (e->map_v[i])
			// {
			// 	e->map_v[i] = ft_strjoin(e->map_v[i], " ");
			// 	e->map_v[i] = ft_strjoin(e->map_v[i], tmp);
			// }
			// else
			// 	e->map_v[i] = ft_strjoin("", tmp);
			// ft_strdel(&tmp);
			ft_printf("L%d-%s ", a->nb_ants, e->table_r[a->p->path[a->p->i]]->name);
			a->p->i++;
		}
		if (a->next == NULL && not_all_printed(e->a))
		{
			if (a->nb_ants == 4)
				e->table_r[a->p->path[a->p->i]]->occuped = 0;
			ft_putchar('\n');
			zero_vistid(e);
			a = e->a;
		}
		else
			a = a->next;
	}
	// e->map_v[i] = NULL;
	// i = 0;
	// while (e->map_v[i])
	// {
	// 	ft_putendl(e->map_v[i]);
	// 	i++;
	// 	i++;
	// }
}
