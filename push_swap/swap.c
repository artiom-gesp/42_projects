/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 11:45:50 by agesp             #+#    #+#             */
/*   Updated: 2019/01/25 09:59:50 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	swap(t_push *p, int print, int which)
{
	int save;

	save = 0;
	p = get_top_list(p);
	if (p && p->next && p->is_data && p->next->is_data)
	{
		save = p->data;
		p->data = p->next->data;
		p->next->data = save;
	}
	if (print)
	{
		if (which == 1)
			write(1, "sa\n", 3);
		else
			write(1, "sb\n", 3);
	}
}

void	swap_both(t_push *a, t_push *b, int print)
{
	swap(a, 0, 1);
	swap(b, 0, 0);
	if (print)
	{
		write(1, "ss\n", 3);
	}
}

void	push(t_push *a, t_push *b, int print, int which)
{
	a = get_top_list(a);
	b = get_top_list(b);
	if (b->is_data)
		b = b->prev;
	if (a->is_data)
	{
		b->data = a->data;
		a->is_data = 0;
		a->data = 0;
		b->is_data = 1;
		b->color = a->color;
		a->color = 0;
	}
	if (print)
	{
		if (which == 1)
			write(1, "pa\n", 3);
		else
			write(1, "pb\n", 3);
	}
}

void	rotate(t_push *p, int print, int which)
{
	int save;

	p = get_top_list(p);
	save = 0;
	if (p->next)
	{
		save = p->data;
		while (p->next)
		{
			p->data = p->next->data;
			p = p->next;
		}
		p->data = save;
	}
	if (print)
	{
		if (which == 1)
			write(1, "ra\n", 3);
		else
			write(1, "rb\n", 3);
	}
}

void	rotate_both(t_push *a, t_push *b, int print)
{
	rotate(a, 0, 1);
	rotate(b, 0, 0);
	if (print)
	{
		write(1, "rr\n", 3);
	}
}
