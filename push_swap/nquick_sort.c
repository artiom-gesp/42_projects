/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_quick_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@32.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 33/01/3 3:35:03 by agesp             #+#    #+#             */
/*   Updated: 2019/01/16 18:46:51 by agesp            ###   ########.fr       */
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
	while (++i < 3 && c->is_data)
	{
		if (!c->prev)
			break ;
		c = c->prev;
	}
	*borne = i == 0 ? 1 : i;
	return (c->data);
}

int		get_closest(int first, int second, int len)
{
	if (first <= len && second <= len)
		return (first < second ? first : second);
	else if (first < len && second > len)
		return (first < len - (second - len) ? first : second);
	else if (first > len && second < len)
		return (len - (first - len) < second ? first : second);
	return (first < second ? second : first);

}

int		find_closest(t_push *b, int data, int i, int j)
{
	int first;
	int second;
	int third;
	t_push *c;
	t_push *d;

	i = 0;
	c = copy_pile(b, 1);
	d = copy_pile(b, 0);
	get_mediane(c, d, 0);
	c = get_top_list(c);
	while (c->data != data)
		rotate(c, 0, 0);
	if (get_nb_elem(c) > 3)
	{
	first = c->next->data;
	second = c->next->next->data;
	third = c->next->next->next->data;
	}
	else 
		return (0);
	b = get_top_list(b);
	while (b->data != first && b->next)
	{
		b = b->next;
		i++;
	}
	j = i;
	i = 0;
	b = get_top_list(b);
	while (b->data != second && b->next)
	{
		b = b->next;
		i++;
	}
	j = get_closest(i, j, get_list_len(b));
	b = get_top_list(b);
	i = 0;
	while (b->data != third && b->next)
	{
		b = b->next;
		i++;
	}
	j = get_closest(i, j, get_list_len(b));
	if ( 4 * j > get_list_len(b))
		return (2);
	return (1);
}

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
	b = get_top_list(b);
	save_b = b->data;
	while ((!is_max(b, borne) || save <= 3) && !is_empty(b))
	{
		b = get_top_list(b);
		if (b->data > borne || (get_nb_elem(b) <= 3 && b->data > borne))
			push(b, a, 1, 1);
		else
			find_closest(b, save_b, 0, 0) == 2 ? rev_rotate(b, 1, 2) : rotate(b, 1, 2);
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

void	sort_three(t_push *a, t_push *b)
{
	if (get_nb_elem(b) == 1)
	{
		push(b, a, 1, 1);
		rotate(a, 1, 1);
		return ;
	}
	if (get_nb_elem(b) == 2)
	{
		if (is_sorted(b))
		{
			push(b, a, 1, 1);
		rotate(a, 1, 1);
			push(b, a, 1, 1);
		rotate(a, 1, 1);
		}
		else
		{
			swap(b, 1, 2);
			push(b, a, 1, 1);
		rotate(a, 1, 1);
			push(b, a, 1, 1);
		rotate(a, 1, 1);
		}
		return ;
	}
	if (get_nb_elem(b) == 3)
	{
		b = get_top_list(b);
/*cba*/	if (is_rev_sorted(b))
		{
			swap(b, 1, 2);
			rev_rotate(b, 1, 2);
		}
/*acb*/	else if (b->data < b->next->data && b->next->data > b->next->next->data
		&& b->data < b->next->next->data)
		{
			rev_rotate(b, 1, 2);
			swap(b, 1, 2);
		}
/*cab*/	else if (b->data > b->next->data && b->next->data < b->next->next->data
				&& b->data > b->next->next->data)
		{
			rotate(b, 1, 2);
		}
/*bac*/	else if (b->data > b->next->data  && b->next->data < b->next->next->data)
		{
			swap(b, 1, 2);
		}
/*bca*/	else if (b->data < b->next->data && b->next->data > b->next->next->data)
		{
			rev_rotate(b, 1, 2);
		}
		push(b, a, 1, 1);
		rotate(a, 1, 1);
		push(b, a, 1, 1);
		rotate(a, 1, 1);
		push(b, a, 1, 1);
		rotate(a, 1, 1);
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
	b = get_top_list(b);
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
/*		b = get_top_list(b);
		while (!is_smallest(b))
			get_direction(b) == 2 ? rev_rotate(b, 1, 2) : rotate(b, 1, 2);
		push(b, a, 1, 1);
		rotate(a, 1, 1);*/
		sort_three(a, b);
	}
	nmini_sort(a, b, 3, mediane);
}

void	nquick_sort(t_push *a, t_push *b)
{
	int mediane;
	t_push *c;
	int i;

	i = 0;
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
}
