/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:12:11 by agesp             #+#    #+#             */
/*   Updated: 2019/01/10 17:50:12 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_push *copy_pile(t_push *p)
{
	t_push *ret;

	p = get_start_list(p);
	if (!(ret = malloc(sizeof(t_push))))
		return (NULL);
	ret->next = NULL;
	ret->data = p->data;
	p->is_data = p->is_data;
	p->prev = NULL;
	while (p->next)
	{
		if (!(ret->next = malloc(sizeof(t_push))))
			return (NULL);
		ret->next->next = NULL;
		ret->next->prev = ret;
		ret->next->data = p->next->data;
		ret->next->is_data = p->next->is_data;
		ret = ret->next;
		p = p->next;
	}
	ret = get_start_list(ret);
	return (ret);
}

int		get_pile_size(t_push *p)
{
	int i;

	i = 0;
	p = get_top_list(p);
	while (p)
	{
		i++;
		if (!p->next)
			break ;
		p = p->next;
	}
	return (i);
}

int		is_min(t_push *p, int min)
{
	p = get_top_list(p);
	while (p)
	{
		if (p->data < min)
			return (0);
		if (!p->next)
			break ;
		p = p->next;
	}
	p = get_top_list(p);
	return (1);
}

void	quick_sort(t_push *a, t_push *b)
{
	int pivot;

	if (is_sorted(a) && is_full(a))
		return ;
	a = get_top_list(a);
	pivot = a->data;
	print_plist(a,b);
	while (!is_min(a, pivot))
	{
		ft_printf("pivot : %d\n", pivot);
		rotate(a);
		print_plist(a, b);
		write(0, "ra\n", 3);
		push(a, b);
		print_plist(a, b);
		write(0, "pb\n", 3);
	}
	swap(a);
	print_plist(a, b);
	write(0, "sa\n", 3);
	ft_printf("size %d\n", get_pile_size(a));
	if (get_pile_size(a) == 1)
	{
		get_mediane(b, a);
		get_mediane(a, b);
		print_plist(a,b);
		return ;
	}
	return (quick_sort(a, b));
}
