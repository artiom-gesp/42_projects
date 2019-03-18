/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 18:03:46 by kecosmon          #+#    #+#             */
/*   Updated: 2017/11/21 18:03:47 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list *list;

	list = *alst;
	while (list)
	{
		if (list->content)
			ft_lstdelone(&list, del);
		(*alst) = (*alst)->next;
		list = *alst;
	}
	*alst = NULL;
}
