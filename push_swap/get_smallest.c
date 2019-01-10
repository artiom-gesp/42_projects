/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_smallest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 14:18:27 by agesp             #+#    #+#             */
/*   Updated: 2019/01/10 16:10:39 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		is_smallest(t_push *p)
{
	int data;

	data = p->data;
	p = get_top_list(p);
	while (p)
	{
		if (p->data < data)
			return (0);
		p = p->next;
	}
	return (1);
}

int		get_mediane(t_push *a, t_push *b)
{
	int mediane;
	int i;

	i = 0;
	mediane = get_list_len(a) / 2;
	while (!is_sorted(a))
	{
		a = get_top_list(a);
		while (!is_smallest(a))
		{
			i++;
			rotate(a);
		}
		i++;
		push(a, b);
	}
	while (!is_full(a))
	{
		i++;
		push(b, a);
	}
	a = get_start_list(a);
	while (mediane--)
	{
		i++;
		a = a->next;
	}
	ft_printf("%d\n", i);
	return (a->data);
}
