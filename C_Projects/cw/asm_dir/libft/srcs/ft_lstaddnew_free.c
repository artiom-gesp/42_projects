/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddnew_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 04:56:39 by amanuel           #+#    #+#             */
/*   Updated: 2019/04/15 18:55:53 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstaddnew_free(t_list *old, void **content, size_t content_size)
{
	t_list	*fresh;

	fresh = (t_list*)ft_memalloc(sizeof(t_list));
	if (content && *content)
		fresh->content = *content;
	*content = NULL;
	if (content_size)
		fresh->content_size = content_size;
	if (old)
		old->next = fresh;
	return (fresh);
}
