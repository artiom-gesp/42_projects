/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_quick_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:35:03 by agesp             #+#    #+#             */
/*   Updated: 2019/01/15 17:38:41 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static int		is_max(t_push *p, int data)
{
	p = get_top_list(p);
	if (p->data > data)
		return (0);
	while (p->next)
	{
		if (p->next->data > data)
			return (0);
		p = p->next;
	}
	return (1);
}

static int		is_min(t_push *p, int data)
{
	p = get_top_list(p);
	if (p->data < data)
		return (0);
	while (p->next)
	{
		if (p->next->data < data)
			return (0);
		p = p->next;
	}
	return (1);
}

static int		get_nb_elem(t_push *p)
{
	int i;

	i = 1;
	p = get_top_list(p);
	if (!p)
		return (0);
	while (p->next)
	{
		i++;
		p = p->next;
	}
	return (i);
}

int		get_borne(t_push *p, int mediane, int *borne)
{
	int i;
	t_push *c;
	t_push *d;

	(void)mediane;
	c = copy_pile(p, 1);
	d = copy_pile(p, 0);
	get_mediane(c, d, 0);
	i = -1;
	c = get_end_list(c);
	while (++i < 8 && c->prev)
		c = c->prev;
	*borne = i;
	return (c->data);
}

void	send_them_back(t_push *a, t_push *b, int mediane, int *i)
{
	int borne;
	
	if (is_empty(b))
		return ;
	borne = get_borne(b, mediane, i);
	while (!is_max(b, borne))
	{
		b = get_top_list(b);
		if (b->data > borne)
			push(b, a, 1, 1);
		else
			rotate(b, 1, 2);
	}
	send_them_back(a, b, mediane, i);
}

void	split_in_half(t_push *a, t_push *b, int mediane)
{
	a = get_top_list(a);
	while (!is_min(a, mediane))
	{
		a = get_top_list(a);
		if (a->data < mediane)
			push(a, b, 1, 2);
		else
			rotate(a, 1, 1);
	}
}

void	nmini_sort(t_push *a, t_push *b, int first, int mediane)
{
	int i;

	i = 0;
	a = get_top_list(a);
	b = get_top_list(b);
	if (b->data == mediane)
		return ;
	while (!is_empty(a) && i < first)
	{
		push(a, b, 1, 2);
		i++;
	}
	while (!is_empty(b))
	{
		while (!is_smallest(b))
			get_direction(b) == 2 ? rev_rotate(b, 1, 2) : rotate(b, 1, 2);
		push(b, a, 1, 1);
		rotate(a, 1, 1);
	}
	nmini_sort(a, b, 8, mediane);
}

void	nquick_sort(t_push *a, t_push *b)
{
	int mediane;
	t_push *c;
	int i;

	if (is_sorted(a))
		return ;
	c = copy_pile(a, 1);
	if (get_list_len(a) < 7)
	{
		is_max(a, 1);
		get_nb_elem(a);
		get_mediane(a, b, 1);
		return ;
	}
	else
	{
		mediane = get_mediane(c, b, 0);
		split_in_half(a, b, mediane);
		send_them_back(a, b, mediane, &i);
		nmini_sort(a, b, i, mediane);
	}
}
