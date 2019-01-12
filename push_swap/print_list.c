/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 18:04:38 by agesp             #+#    #+#             */
/*   Updated: 2019/01/12 18:05:05 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	print_plist(t_push *a, t_push *b)
{
	a = get_start_list(a);
	b = get_start_list(b);
	ft_printf("#########################################\n");
	while (a)
	{
		ft_printf("%d %*d\n", a->data, a->data < 0 ? (40 - ft_nbrlen(a->data) - 1)
				: (40 - ft_nbrlen(a->data)), b->data);
		if (!a->next)
			break ;
		a = a->next;
		b = b->next;
	}
	ft_printf("#########################################\n");
}

int		len_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
