/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:20:43 by agesp             #+#    #+#             */
/*   Updated: 2018/11/12 09:20:55 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*save_list;
	t_list	*save_next;

	save_list = lst;
	save_next = lst;
	if (lst)
		while (save_list)
		{
			save_next = save_list->next;
			(*f)(save_list);
			save_list = save_next;
		}
}
