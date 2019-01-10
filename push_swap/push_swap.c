/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:50:53 by agesp             #+#    #+#             */
/*   Updated: 2019/01/10 14:40:04 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		get_list_len(t_push *p)
{
	int i;

	i = 0;
	p = get_start_list(p);
	while (p->next)
	{
		p = p->next;
		i++;
	}
	return (i);
}

int		is_empty(t_push *list)
{
	list = get_start_list(list);
	while (list)
	{
		if (list->is_data)
			return (0);
		list = list->next;
	}
	return (1);
}

void	push_swap(t_push *a, t_push *b)
{
	int len;
	int i;

	i = 0;
	len = get_list_len(a);
	if (is_sorted(a))
		return ;
	if (len == 1)
		return ;
	else if (len == 2)
	{
		if (!is_sorted(a))
		{
			swap(a);
			i++;
			write(0, "sa\n", 3);
		}
		ft_printf("%d\n", i);
		return ;
	}
	else
	{
		while ((!is_full(b) || is_empty(b)))
		{
			while (is_rev_sorted(b) && !is_empty(a))
			{
				push(a, b);
				i++;
				write(0, "pb\n", 3);
			}
			while (!is_rev_sorted(b))
			{
				i += 2;
				swap(b);
				push(b, a);
				write(0, "sb\n", 3);
				write(0, "pa\n", 3);
			}
			if (is_full(b) && is_rev_sorted(b))
			{
				while (!is_full(a))
				{
					i++;
					push(b, a);
					write(0, "pa\n\n", 4);
				}
				ft_printf("%d\n", i);
				return ;
			}
		}
	}
}
