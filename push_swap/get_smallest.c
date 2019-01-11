/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_smallest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 14:18:27 by agesp             #+#    #+#             */
/*   Updated: 2019/01/11 16:42:03 by agesp            ###   ########.fr       */
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

int		get_direction(t_push *a)
{
	t_push *s;
	int		i;
	int		j;

	s = copy_pile(a, 1);
	i = 0;
	j = 0;
	s = get_top_list(s);
	while (!is_smallest(s))
	{
		rotate(s);
		i++;
	}
	j = get_list_len(s);
	if (i > j / 2)
		return (2);
	return (1);
}

int		get_mediane(t_push *a, t_push *b)
{
	int mediane;
	//t_push *a;
	//t_push *b;
	int i;
	int j;

	i = 0;
	j = 0;
	//a = copy_pile(c, 1);
//	b = copy_pile(d, 0);
	mediane = get_list_len(a) / 2;
	while (!is_sorted(a))
	{
		a = get_top_list(a);
		j = get_direction(a);
		while (!is_smallest(a))
		{
			i++;
			j == 2 ? rev_rotate(a) : rotate(a);
			a = get_top_list(a);
			if (a->next && a->next->data < a->data)
			{
				swap(a);
				i++;
			}
		}
		if (a->next && a->next->data < a->data)
		{
			i++;
			swap(a);
		}
		i++;
		a = get_top_list(a);
		push(a, b);
	}
	while (!is_full(a) && !is_empty(b))
	{
		i++;
		push(b, a);
	}
	ft_printf("i %d\n", i);
	a = get_start_list(a);
	while (mediane--)
	{
		i++;
		a = a->next;
	}
	i = a->data;
//	free_list(a);
//	free_list(b);
	return (i);
}
