/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:54:58 by agesp             #+#    #+#             */
/*   Updated: 2019/01/10 10:46:40 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		is_full(t_push *list)
{
	list = get_start_list(list);
	while (list->next)
	{
		if (!list->is_data)
			return (0);
		list = list->next;
	}
	return (1);
}

int		is_sorted(t_push *list)
{
	list = get_top_list(list);
	while (list->next)
	{
		if (list->data >= list->next->data)
			return (0);
		list = list->next;
	}
	return (1);
}

int		do_check(t_push *a, t_push *b, char *instruction, int flag)
{
	if (!ft_strcmp(instruction, "sa"))
		swap(a);
	else if (!ft_strcmp(instruction, "sb"))
		swap(b);
	else if (!ft_strcmp(instruction, "ss"))
		swap_both(a, b);
	else if (!ft_strcmp(instruction, "pa"))
		push(b, a);
	else if (!ft_strcmp(instruction, "pb"))
		push(a, b);
	else if (!ft_strcmp(instruction, "ra"))
		rotate(a);
	else if (!ft_strcmp(instruction, "rb"))
		rotate(b);
	else if (!ft_strcmp(instruction, "rr"))
		rotate_both(a, b);
	else if (!ft_strcmp(instruction, "rra"))
		rev_rotate(a);
	else if (!ft_strcmp(instruction, "rrb"))
		rev_rotate(b);
	else if (!ft_strcmp(instruction, "rrr"))
		rev_rotate_both(a, b);
	else
		return (0);
	if (flag)
		print_plist(a, b);
	return (1);
}
