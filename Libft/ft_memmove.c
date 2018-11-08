/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:20:01 by agesp             #+#    #+#             */
/*   Updated: 2018/11/07 17:25:19 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int i;
	char *savedst;
	char *savesrc;

	i = 0;
	savedst = (char*)dst;
	savesrc = (char*)src;
	while (i < n && savesrc[i])
	{
		
		i++;
	}
	dst = savedst;
	return (dst);
}


