/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rota.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 16:44:48 by agesp             #+#    #+#             */
/*   Updated: 2019/01/24 16:45:47 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	rev_rotate(t_push *p, int print, int which)
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
		if (which == 1)
			write(1, "rra\n", 4);
		else
			write(1, "rrb\n", 4);
	}
}

void	rev_rotate_both(t_push *a, t_push *b, int print)
{
	rev_rotate(a, 0, 0);
	rev_rotate(b, 0, 0);
	if (print)
	{
		write(1, "rrr\n", 4);
	}
}
