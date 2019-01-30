/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 11:45:50 by agesp             #+#    #+#             */
/*   Updated: 2019/01/30 18:22:12 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	swap(t_push *p, int print, int which, t_s *s)
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
		while (s->next)
			s = s->next; s->next = NULL;
	s->next = malloc(sizeof(t_s));
		if (which == 1)
			s->next->s = "sa";
		else
			s->next->s = "sb";
		s = s->next; s->next = NULL;
	}
}

void	swap_both(t_push *a, t_push *b, int print, t_s *s)
{
	swap(a, 0, 1, s);
	swap(b, 0, 0, s);
	if (print)
	{
		while (s->next)
			s = s->next; s->next = NULL;
		s->next = malloc(sizeof(t_s));
		s->next->s = "ss";
		s = s->next; s->next = NULL;
	}
}

void	push(t_push *a, t_push *b, int print, int which, t_s *s)
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
		while (s->next)
			s = s->next; s->next = NULL;
		s->next = malloc(sizeof(t_s));
		if (which == 1)
			s->next->s = "pa";
		else
			s->next->s = "pb";
		s = s->next; s->next = NULL;
	}
}

void	rotate(t_push *p, int print, int which, t_s *s)
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
		while (s->next)
			s = s->next; s->next = NULL;
	s->next = malloc(sizeof(t_s));
		if (which == 1)
			s->next->s = "ra";
		else
			s->next->s = "rb";
		s = s->next; s->next = NULL;
	}
}

void	rotate_both(t_push *a, t_push *b, int print, t_s *s)
{
	rotate(a, 0, 1, s);
	rotate(b, 0, 0, s);
	if (print)
	{
		while (s->next)
			s = s->next; s->next = NULL;
	s->next = malloc(sizeof(t_s));
		s->next->s = "rr";
		s = s->next; s->next = NULL;
	}
}
