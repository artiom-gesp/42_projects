/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:12:11 by agesp             #+#    #+#             */
/*   Updated: 2019/01/11 15:29:18 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_push *copy_pile(t_push *p, int is_data)
{
	t_push *ret;

	p = get_start_list(p);
	if (!(ret = malloc(sizeof(t_push))))
		return (NULL);
	ret->next = NULL;
	ret->data = is_data ? p->data : 0;
	ret->is_data = p->is_data;
	ret->prev = NULL;
	while (p->next)
	{
		if (!(ret->next = malloc(sizeof(t_push))))
			return (NULL);
		ret->next->next = NULL;
		ret->next->prev = ret;
		ret->next->data = is_data ? p->next->data : 0;
		ret->next->is_data = is_data ? p->next->is_data : 0;
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
	if (!p->next)
		return (1);
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

void	quick_sort(t_push *a, t_push *b, int flag)
{
	int pivot;
	static int		i = 0;

	(void)flag;
	a = get_top_list(a);
	pivot = a->data;
	//print_plist(a, b);
	if (is_sorted(a) && is_full(a))
		return ;
	while (!is_empty(a))
	{
		while (!is_min(a, pivot))
		{
			rotate(a);
			//		print_plist(a, b);
			i++;
			while (a->data < pivot)
			{
				push(a, b);
				a = get_top_list(a);
				//				print_plist(a, b);
				b = get_top_list(b);
				if (b->next && b->data < b->next->data)
				{
					swap(b);
					//					print_plist(a, b);
					i++;
				}
				i++;
			}
		}
		while (a->data != pivot)
		{
			rotate(a);
			//			print_plist(a, b);
			i++;
		}
		push(a,b);
		//		print_plist(a, b);
		i++;
		b = get_top_list(b);
		if (b->next && b->next->data > b->data)
		{
			swap(b);
			//			print_plist(a, b);
			i++;
		}
		while (!is_empty(a))
		{
			a = get_top_list(a);
			push(a, b);
			//			print_plist(a, b);
			i++;

			b = get_top_list(b);
			if (b->next && b->data < b->next->data)
			{
				swap(b);
				//				print_plist(a, b);
				i++;
			}
		}
	}
	b = get_top_list(b);
	pivot = b->data;
	if (!is_rev_sorted(b))
	{
		while (!is_empty(b))
		{
			while (!is_min(b, pivot))
			{
				rotate(b);
				//		print_plist(a, b);
				i++;
				while (b->data < pivot && b->next)
				{
					push(b, a);
					b = get_top_list(b);
					//				print_plist(a, b);
					a = get_top_list(a);
					if (a->next && a->data > a->next->data)
					{
						swap(a);
						//					print_plist(a, b);
						i++;
					}
					i++;
				}
			}
			while (b->data != pivot)
			{
				rotate(b);
				//			print_plist(a, b);
				i++;
			}
			push(b, a);
			//		print_plist(a, b);
			i++;
			a = get_top_list(a);
			if (a->next && a->next->data > a->data)
			{
				swap(a);
				//			print_plist(a, b);
				i++;
			}
			while (!is_empty(b))
			{
				b = get_top_list(b);
				push(b, a);
				//			print_plist(a, b);
				i++;

				a = get_top_list(a);
				if (a->next && a->data > a->next->data)
				{
					swap(a);
					//				print_plist(a, b);
					i++;
				}
			}
		}
	}
	else
	{
		b = get_top_list(b);
		while (!is_empty(b))
		{
			push(b, a);
			i++;
		}
	}
	ft_printf("i %d\n", i);
	return (quick_sort(a, b, 1));
}
