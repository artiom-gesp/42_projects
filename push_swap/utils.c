/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 15:37:49 by agesp             #+#    #+#             */
/*   Updated: 2019/01/24 17:10:06 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		is_max(t_push *p, int data)
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

int		is_min(t_push *p, int data)
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

int		get_nb_elem(t_push *p)
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
	int		i;
	t_push	*c;
	t_push	*d;

	(void)mediane;
	c = copy_pile(p, 1);
	d = copy_pile(p, 0);
	get_mediane(c, d, 0);
	i = -1;
	c = get_end_list(c);
	while (++i < (get_list_len(p) > 200
				? 20 : get_list_len(p) / 10) && c->is_data)
	{
		if (!c->prev)
			break ;
		c = c->prev;
	}
	*borne = i == 0 ? 1 : i;
	i = c->data;
	free_list(c);
	free_list(d);
	return (c->data);
}