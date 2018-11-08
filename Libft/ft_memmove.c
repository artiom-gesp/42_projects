/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:42:03 by agesp             #+#    #+#             */
/*   Updated: 2018/11/08 10:52:28 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int i;
	char *savedst;
	char *savesrc;
	char save[n];

	i = 0;
	savedst = (char*)dst;
	savesrc = (char*)src;
	while (i < n)
	{
		save[i] = savesrc[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		savedst[i] = save[i];
		i++;
	}
	dst = savedst;
	return (dst);
}


