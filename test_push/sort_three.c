/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 11:46:16 by agesp             #+#    #+#             */
/*   Updated: 2019/01/30 18:02:51 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	sort_three(t_push *a, int print, t_s *s)
{
	a = get_top_list(a);
	if (is_rev_sorted(a))
	{
		swap(a, 1, print, s);
		rev_rotate(a, 1, print, s);
	}
	else if (a->data < a->next->data && a->next->data > a->next->next->data
			&& a->data < a->next->next->data)
	{
		rev_rotate(a, 1, print, s);
		swap(a, 1, print, s);
	}
	else if (a->data > a->next->data && a->next->data < a->next->next->data
			&& a->data > a->next->next->data)
		rotate(a, 1, print, s);
	else if (a->data > a->next->data && a->next->data < a->next->next->data)
		swap(a, 1, print, s);
	else if (a->data < a->next->data && a->next->data > a->next->next->data)
		rev_rotate(a, 1, print, s);
}

void	reverse_sort_three(t_push *a, t_push *b, t_s *s)
{
	b = get_top_list(b);
	a = get_top_list(a);
	if (is_sorted(b))
	{
		is_sorted(a) ? swap(b, 1, 2, s) : swap_both(a, b, 1, s);
		rev_rotate(b, 1, 2, s);
	}
	else if (b->data < b->next->data && b->next->data > b->next->next->data
			&& b->data < b->next->next->data)
		rotate(b, 1, 2, s);
	else if (b->data > b->next->data && b->next->data < b->next->next->data
			&& b->data > b->next->next->data)
	{
		is_sorted(a) ? swap(b, 1, 2, s) : swap_both(a, b, 1, s);
		rotate(b, 1, 2, s);
	}
	else if (b->data > b->next->data && b->next->data < b->next->next->data)
		rev_rotate(b, 1, 2, s);
	else if (b->data < b->next->data && b->next->data > b->next->next->data)
		is_sorted(a) ? swap(b, 1, 2, s) : swap_both(a, b, 1, s);
}

void	set_max(t_push *a, t_push *b, t_s *s)
{
	a = get_top_list(a);
	if (is_max(a, a->data))
		rotate(a, 1, 1, s);
	else if (is_max(a, a->next->data))
	{
		rotate(a, 1, 1, s);
		rotate(a, 1, 1, s);
	}
	else if (is_max(a, a->next->next->data))
		rev_rotate(a, 1, 1, s);
	if (is_max(a, a->next->next->next->data))
		while (get_nb_elem(a) > 2)
			push(a, b, 1, 2, s);
	else
		while ((get_nb_elem(a) > 2 && !is_max(b, a->data))
				|| get_nb_elem(b) < 2)
		{
			a = get_top_list(a);
			if (get_nb_elem(a) == 4 && is_max(b, a->data)
					&& a->data > a->next->data)
				swap(a, 1, 1, s);
			push(a, b, 1, 2, s);
			a = get_top_list(a);
		}
}

void	sort_five(t_push *a, t_push *b, t_s *s)
{
	set_max(a, b, s);
	if (get_nb_elem(b) == 2 && is_sorted(b))
		swap(b, 1, 2, s);
	else if (get_nb_elem(b) == 3)
		reverse_sort_three(a, b, s);
	if (!is_sorted(a))
		swap(a, 1, 1, s);
	while (!is_empty(b))
	{
		push(b, a, 1, 1, s);
		a = get_top_list(a);
		if (a->data > a->next->next->data)
			rotate(a, 1, 1, s);
		else if (a->data > a->next->data)
			swap(a, 1, 1, s);
	}
}
