/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 11:45:50 by agesp             #+#    #+#             */
/*   Updated: 2019/01/09 14:50:17 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	swap(t_push *p)
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
}

void	swap_both(t_push *a, t_push *b)
{
	swap(a);
	swap(b);
}

void	push(t_push *a, t_push *b)
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
	}
}

void	rotate(t_push *p)
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
}

void	rotate_both(t_push *a, t_push *b)
{
	rotate(a);
	rotate(b);
}

void	rev_rotate(t_push *p)
{
	int save;

	p = get_end_list(p);
	save = 0;
	if (p->prev)
	{
		save = p->data;
		while (p->prev && p->prev->is_data)
		{
			p->data = p->prev->data;
			p = p->prev;
		}
		p->data = save;
	}
}

void	rev_rotate_both(t_push *a, t_push *b)
{
	rev_rotate(a);
	rev_rotate(b);
}
