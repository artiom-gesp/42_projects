/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rota.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:44:48 by agesp             #+#    #+#             */
/*   Updated: 2019/01/30 18:23:11 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	rev_rotate(t_push *p, int print, int which, t_s *s)
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
	if (print)
	{
		while (s->next)
			s = s->next; s->next = NULL;
		s->next = malloc(sizeof(t_s));
		if (which == 1)
			s->next->s = "rra";
		else
			s->next->s = "rrb";
		s = s->next; s->next = NULL;
	}
}

void	rev_rotate_both(t_push *a, t_push *b, int print, t_s *s)
{
	rev_rotate(a, 0, 0, s);
	rev_rotate(b, 0, 0, s);
	if (print)
	{
		while (s->next)
			s = s->next; s->next = NULL;
		s->next = malloc(sizeof(t_s));
		s->next->s = "rrr";
		s = s->next; s->next = NULL;
	}
}
