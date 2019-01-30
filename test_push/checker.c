/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 14:54:58 by agesp             #+#    #+#             */
/*   Updated: 2019/01/30 18:01:13 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		is_full(t_push *list)
{
	list = get_start_list(list);
	while (list)
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

int		is_rev_sorted(t_push *list)
{
	list = get_top_list(list);
	while (list->next)
	{
		if (list->next->data >= list->data)
			return (0);
		list = list->next;
	}
	return (1);
}

void	get_color(t_push *a, t_push *b, char *instruction)
{
	b = get_top_list(b);
	a = get_top_list(a);
	if (!ft_strcmp(instruction, "sa") && a->is_data)
		a->color = 1;
	else if (!ft_strcmp(instruction, "sb") && b->is_data)
		b->color = 1;
	else if (!ft_strcmp(instruction, "pa"))
		b->color = 1;
	else if (!ft_strcmp(instruction, "pb"))
		a->color = 1;
	else if (!ft_strcmp(instruction, "ra"))
		a->color = 1;
	else if (!ft_strcmp(instruction, "rb"))
		b->color = 1;
	else if (!ft_strcmp(instruction, "rra"))
		a->color = 1;
	else if (!ft_strcmp(instruction, "rrb"))
		b->color = 1;
}

int		do_check(t_push *a, t_push *b, char *instruction)
{
	t_s *s;
	s = NULL;
	if (!ft_strcmp(instruction, "sa"))
		swap(a, 0, 0, s);
	else if (!ft_strcmp(instruction, "sb"))
		swap(b, 0, 0, s);
	else if (!ft_strcmp(instruction, "ss"))
		swap_both(a, b, 0, s);
	else if (!ft_strcmp(instruction, "pa"))
		push(b, a, 0, 0, s);
	else if (!ft_strcmp(instruction, "pb"))
		push(a, b, 0, 0, s);
	else if (!ft_strcmp(instruction, "ra"))
		rotate(a, 0, 0, s);
	else if (!ft_strcmp(instruction, "rb"))
		rotate(b, 0, 0, s);
	else if (!ft_strcmp(instruction, "rr"))
		rotate_both(a, b, 0, s);
	else if (!ft_strcmp(instruction, "rra"))
		rev_rotate(a, 0, 0, s);
	else if (!ft_strcmp(instruction, "rrb"))
		rev_rotate(b, 0, 0, s);
	else if (!ft_strcmp(instruction, "rrr"))
		rev_rotate_both(a, b, 0, s);
	else
		return (0);
	return (1);
}
