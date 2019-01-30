/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nquick_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 15:47:27 by agesp             #+#    #+#             */
/*   Updated: 2019/01/30 13:05:33 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	send_them_back(t_push *a, t_push *b, int mediane, int *i)
{
	int borne;
	int save;
	int save_b;

	if (is_empty(b))
		return ;
	borne = get_borne(b, mediane, i);
	if (get_nb_elem(b) == 1)
	{
		push(b, a, 1, 1);
		return ;
	}
	save = get_nb_elem(b);
	save_b = b->data;
	while ((!is_max(b, borne) || save <= (get_list_len(a) > 200 ? 20 : get_list_len(a) / 10)) && !is_empty(b))
	{
		b = get_top_list(b);
		if (b->data > borne || save <= (get_list_len(a) > 200 ? 20 : get_list_len(a) / 10))
			push(b, a, 1, 1);
		else
			rotate(b, 1, 2);
	}
	send_them_back(a, b, mediane, i);
}

void	split_in_half(t_push *a, t_push *b, int mediane, int flag)
{
	if (flag)
	{
		a = get_top_list(a);
		while (!is_smallest(a))
		{
			push(a, b, 1, 2);
			a = get_top_list(a);
		}
	}
	else
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
}

int		is_next_sorted(t_push *p)
{
	int last;
	int first;

	p = get_end_list(p);
	last = p->data;
	p = get_top_list(p);
	first = p->data;
	if (first == last + 1)
		return (1);
	if (is_smallest(p))
		return (0);
	while (p->next)
	{
		if (p->data < first && p->data != last)
			return (0);
		p = p->next;
	}
	return (1);
}

void	nmini_sort(t_push *a, t_push *b, int first, int mediane)
{
	int i;

	i = 0;
	a = get_top_list(a);
	if (a->data == mediane || (is_full(a) && is_sorted(a)))
		return ;
	while (!is_empty(a) && i < first && a->data != mediane)
	{
		if (is_next_sorted(a))
			rotate(a, 1, 1);
		else
			push(a, b, 1, 2);
		i++;
		a = get_top_list(a);
	}
	while (!is_empty(b))
	{
		b = get_top_list(b);
		while (!is_smallest(b))
			rotate(b, 1, 2);
		push(b, a, 1, 1);
		rotate(a, 1, 1);
	}
	nmini_sort(a, b, (get_list_len(a) > 200 ? 20 :
				get_list_len(a) / 10), mediane);
}

void	super_sort(t_push *a, t_push *b, t_push *c)
{
	int mediane;
	int i;

	i = 0;
	mediane = get_mediane(c, b, 0);
	split_in_half(a, b, mediane, 0);
	a = get_top_list(a);
	while (a->data != mediane)
		rotate(a, 1, 1);
	send_them_back(a, b, mediane, &i);
	nmini_sort(a, b, i, mediane);
	rotate(a, 1, 1);
	split_in_half(a, b, mediane, 1);
	send_them_back(a, b, mediane, &i);
	nmini_sort(a, b, i, mediane);
}
