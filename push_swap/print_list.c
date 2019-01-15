/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 18:04:38 by agesp             #+#    #+#             */
/*   Updated: 2019/01/15 14:21:40 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	my_sleep(int len)
{
	int i;

	i = 0;
	while (len)
	{
		while (i < 10000)
		{
			free(malloc(1));
			i++;
		}
		len--;
	}
}

void	print_line(int len)
{
	int i;

	i = 0;
	if (i == len)
		return ;
	while (i < len)
	{
		ft_printf("-");
		i++;
	}
}

int		get_pos(t_push *a, int data)
{
	int i;
	t_push *c;

	i = 0;
	if (!(c = copy_pile(a, 1)))
		return (0);
	c = get_top_list(c);
	while (c->data != data)
	{
		rotate(c, 0, 0);
	}
		rotate(c, 0, 0);
	while (c->data != data)
	{
		if (c->data < data)
			i++;
		rotate(c, 0, 0);
	}
	free(c);
	return (i + 1);
}

void	print_plist(t_push *a, t_push *b)
{
	int i;
	int j;
	int max;

	a = get_start_list(a);
	b = get_start_list(b);
	my_sleep(10000000);
	ft_printf("################################################################################################\n");
	while (a)
	{
		i = a->is_data ? get_pos(a, a->data) : 0;
		j = b->is_data ? get_pos(b, b->data) : 0;
		max = i < j ? j : i;
		ft_printf("%3d - ", i);
		print_line(i);
		ft_printf("%*c", 70 - i, 0);
		ft_printf("%3d - ", j);
		print_line(j);
		ft_printf("\n");
			//ft_printf("%d %*d\n", a->data, a->data < 0 ? (40 - ft_nbrlen(a->data) - 1)
		//		: (40 - ft_nbrlen(a->data)), b->data);
		if (!a->next)
			break ;
		a = a->next;
		b = b->next;
	}
	ft_printf("################################################################################################\n");
	my_sleep(10000000);
//	ft_printf("\e[1;1H\e[2J");
	my_sleep(10000000);
}

int		len_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
