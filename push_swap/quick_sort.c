/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 11:47:46 by agesp             #+#    #+#             */
/*   Updated: 2019/01/14 18:54:30 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		is_max(t_push *p, int data)
{
	p = get_top_list(p);
	if (p->data > data)
		return (0);
	while (p->next)
	{
		if (p->next->data > data)
			return (0);
		p = p->next;
	}
	return (1);
}

int		is_min(t_push *p, int data)
{
	p = get_top_list(p);
	if (p->data < data)
		return (0);
	while (p->next)
	{
		if (p->next->data < data)
			return (0);
		p = p->next;
	}
	return (1);
}

int		get_nb_elem(t_push *p)
{
	int i;

	i = 1;
	p = get_top_list(p);
	if (!p)
		return (0);
	while (p->next)
	{
		i++;
		p = p->next;
	}
	return (i);
}

void	cut_in_three(t_push *p, int *b1, int *b2)
{
	int		j;
	int		i;
	t_push *a;
	t_push *b;

	j = 0;
	if (!(a = copy_pile(p, 1)))
		return ;
	if (!(b = copy_pile(p, 0)))
		return ;
	i = get_nb_elem(a);
	get_mediane(a, b, 0);
	a = get_top_list(a);
	while (a->next && j < i / 3)
	{
		j++;
		a = a->next;
	}
	*b1 = j;
	while (a->next && j < 2 * i / 3)
	{
		j++;
		a = a->next;
	}
	*b2 = j;
}


int		get_moy(t_push *p)
{
	int i;

	p = get_top_list(p);
	i = p->data;
	while (p->next)
	{
		i += p->next->data;
		p = p->next;
	}
	return (i /(get_nb_elem(p)));
}

void	split_list(t_push *a, t_push *b)
{
	int moy;


	a = get_top_list(a);
	moy = get_moy(a);
	while (!is_min(a, moy))
	{
		a = get_top_list(a);
		if (a->data < moy)
		{
			push(a, b, 1, 2);
			a = get_top_list(a);
		}
		else
			rotate(a, 1, 1);
	}
}

void	rev_split_list(t_push *a, t_push *b)
{
	int moy;


	a = get_top_list(a);
	moy = get_moy(a);
	while (!is_max(a, moy))
	{
		a = get_top_list(a);
		if (a->data > moy)
		{
			push(a, b, 1, 2);
			a = get_top_list(a);
		}
		else
			rotate(a, 1, 1);
	}
}

void	split_in_three(t_push *a, t_push *b, int *b1, int *b2, int part2)
{
	cut_in_three(b, b1, b2);
	*b1 += part2;
	*b2 += part2;
	while (!is_empty(b))
	{
		b = get_top_list(b);
		while (!is_max(b, *b2))
		{
			if (b->data > *b2)
			{
				push(b, a, 1, 1);
				a = get_top_list(a);
				if (a->next && !is_min(a, a->next->data) && a->next->data < a->data)
					swap(a, 1, 1);
				b = get_top_list(b);
			}
			else
				rotate(b, 1, 2);
		}
		if (*b1 == *b2)
			*b2 = 0;
		else
			*b2 = *b1;
	}
}

int		is_biggest(t_push *p)
{
	int data;

	data = p->data;
	p = get_top_list(p);
	while (p)
	{
		if (p->data > data)
			return (0);
		p = p->next;
	}
	return (1);
}	

int		get_biggest_direction(t_push *p)
{
	t_push *s;
	int		i;
	int		j;

	s = copy_pile(p, 1);
	i = 0;
	j = 0;
	s = get_top_list(s);
	while (!is_biggest(s))
	{
		rotate(s, 0, 0);
		i++;
	}
	j = get_list_len(s);
	if (i > j / 2)
		return (2);
	return (1);
}

void	mini_sort(t_push *a, t_push *b, int b1, int b2)
{
	
	while (b1 < b2)
	{
		push(a, b, 1, 2);
		b1++;
	}
	while (!is_empty(b))
	{
		b = get_top_list(b);
		while (!is_smallest(b))
		{
			get_direction(b) == 2 ? rev_rotate(b, 1, 2) : rotate(b, 1, 2);
		}
		push(b, a, 1 , 1);
		rotate(a, 1, 1);
	}
}

void	quick_sort(t_push *a, t_push *b)
{
	int i = 4;
	int b1;
	int b2;

	if (is_sorted(a))
		return ;
	if (get_list_len(a) < 4)
	{
		get_mediane(a, b, 1);
		return ;
	}
	else
	{
		split_list(a, b);
		split_in_three(a, b, &b1, &b2, 0);
		while (--i)
		{
			if (i == 1)
				b1 = (get_list_len(a) / 2) - 2 * b1;
			mini_sort(a, b, 0, b1);
		}
		a = get_top_list(a);
		rev_split_list(a,b);
		a = get_top_list(a);
		if (a->next && a->next->data < a->data)
			rotate(a, 1, 1);
		split_in_three(a, b, &b1, &b2, get_list_len(a) / 2);
		i = 4;
	//	ft_printf("b1 %d\n", b1);
		b1 -= get_list_len(a) / 2;
		while (--i)
		{
			if (i == 1)
				b1 = (get_list_len(a) / 2) - 2 * b1;
			mini_sort(a, b, 0, b1);
		}
	//	mini_sort(a, b, b1, b2);
	//	mini_sort(a, b, b2, get_list_len(a));

	}
}
