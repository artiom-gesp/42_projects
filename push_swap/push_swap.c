/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 17:53:38 by agesp             #+#    #+#             */
/*   Updated: 2019/01/24 18:25:20 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		len_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

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
	return (i + 1);
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

t_push	*copy_pile(t_push *p, int is_data)
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

void	nquick_sort(t_push *a, t_push *b)
{
	t_push *c;

	if (is_sorted(a))
		return ;
	c = copy_pile(a, 1);
	if (get_list_len(a) < 10)
	{
		is_max(a, 1);
		get_nb_elem(a);
		get_mediane(a, b, 1);
		free_list(c);
		return ;
	}
	else
		super_sort(a, b, c);
	free_list(c);
}
