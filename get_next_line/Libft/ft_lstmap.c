/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:21:09 by agesp             #+#    #+#             */
/*   Updated: 2018/11/12 09:21:31 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*save_list;
	t_list	*save_next;

	save_next = NULL;
	if (lst)
	{
		save_list = (*f)(lst);
		save_next = save_list;
		while (lst)
		{
			save_list->next = (*f)(lst->next);
			save_list = save_list->next;
			lst = lst->next;
		}
	}
	return (save_next);
}
