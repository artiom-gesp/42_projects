/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:50:53 by agesp             #+#    #+#             */
/*   Updated: 2019/01/10 12:05:44 by agesp            ###   ########.fr       */
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

void	push_swap(t_push *a, t_push *b)
{
	int len;

	len = get_list_len(a);
	if (is_sorted(a))
		return ;
	if (len == 1)
		return ;
	else if (len == 2)
	{
		if (!is_sorted_list(a))
		{
			swap(a);
			write(0, "sa\n", 3);
		}
		return ;
	}
	else
	{
		while (!is_full(b) && !is_rev_sorted(b))
		{
			while (is_rev_sorted(b))
			{
				push(a, b);
				write(0, "pb\n", 3);
			}
			while (!is_rev_sorted(b))
			{
				swap(b);
				push(b, a);
				write(0, "sb\n", 3);
				write(0, "pa\n", 3);
			}
		}

	}
}

