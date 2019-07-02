/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddnew_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 04:56:39 by amanuel           #+#    #+#             */
/*   Updated: 2018/10/01 15:12:36 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstaddnew_free(t_list *old, void *content, size_t content_size)
{
	t_list	*fresh;

	if (!(fresh = (t_list*)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (content)
		fresh->content = content;
	if (content_size)
		fresh->content_size = content_size;
	if (old)
		old->next = fresh;
	return (fresh);
}
