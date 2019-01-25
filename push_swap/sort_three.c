/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   ay: agesp <marvin@41.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1019/01/15 15:51:00 ay agesp             #+#    #+#             */
/*   Updated: 2019/01/25 18:39:39 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	sort_three(t_push *a, int print)
{
		a = get_top_list(a);
/*cba*/	if (is_rev_sorted(a))
		{
			swap(a, 1, print);
			rev_rotate(a, 1, print);
		}
/*acb*/	else if (a->data < a->next->data && a->next->data > a->next->next->data
		&& a->data < a->next->next->data)
		{
			rev_rotate(a, 1, print);
			swap(a, 1, print);
		}
/*cab*/	else if (a->data > a->next->data && a->next->data < a->next->next->data
				&& a->data > a->next->next->data)
			rotate(a, 1, print);
/*bac*/	else if (a->data > a->next->data  && a->next->data < a->next->next->data)
			swap(a, 1, print);
/*bca*/	else if (a->data < a->next->data && a->next->data > a->next->next->data)
			rev_rotate(a, 1, print);
}

void	reverse_sort_three(t_push *a, t_push *b)
{
		b = get_top_list(b);
		a = get_top_list(a);
/*abc*/	if (is_sorted(b))
		{
			is_sorted(a) ? swap(b, 1, 2) : swap_both(a, b, 1);
			rev_rotate(b, 1, 2);
		}
/*acb*/	else if (b->data < b->next->data && b->next->data > b->next->next->data
		&& b->data < b->next->next->data)
			rotate(b, 1, 2);
/*cab*/	else if (b->data > b->next->data && b->next->data < b->next->next->data
				&& b->data > b->next->next->data)
		{
			is_sorted(a) ? swap(b, 1, 2) : swap_both(a, b, 1);
			rotate(b, 1, 2);
		}
/*bac*/	else if (b->data > b->next->data  && b->next->data < b->next->next->data)
			rev_rotate(b, 1, 2);
/*bca*/	else if (b->data < b->next->data && b->next->data > b->next->next->data)
			is_sorted(a) ? swap(b, 1, 2) : swap_both(a, b, 1);
}

void	sort_five(t_push *a, t_push *b)
{
	a = get_top_list(a);
	if (is_min(a, a->data))
			rotate(a, 1, 1);
	else if (is_min(a, a->next->data))
	{
		rotate(a, 1, 1);
		rotate(a, 1, 1);
	}
	else if (is_min(a, a->next->next->data))
		rev_rotate(a, 1, 1);
	push(a, b, 1, 2);
	push(a, b, 1, 2);
	push(a, b, 1, 2);
	if (!is_sorted(a))
		swap(a, 1, 1);
	a = get_top_list(a);
//	if (is_max(b, a->next->data))
//	{
		reverse_sort_three(a, b);
//	}
//	else
//		sort_three(b, 2);
	while (!is_empty(b))
	{
		b = get_top_list(b);
		push(b, a, 1, 1);
		a = get_top_list(a);
		if (a->data > a->next->next->data)
			rotate(a, 1, 1);
		else
			swap(a, 1, 1);
	}
//	while (!is_sorted(a))
//		rev_rotate(a, 1, 1);
}
