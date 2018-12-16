/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:19:51 by agesp             #+#    #+#             */
/*   Updated: 2018/11/24 17:45:34 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*save_list;
	t_list	*save_next;

	save_list = *alst;
	save_next = save_list->next;
	if (del)
	{
		while (save_next)
		{
			save_next = save_list->next;
			ft_lstdelone(&save_list, del);
			save_list = save_next;
		}
		*alst = NULL;
	}
}
