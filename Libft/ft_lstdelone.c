/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:20:26 by agesp             #+#    #+#             */
/*   Updated: 2018/11/24 16:52:31 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*save_list;

	if (del)
	{
		save_list = *alst;
		(*del)(save_list->content, save_list->content_size);
		free(save_list);
		*alst = NULL;
	}
}
