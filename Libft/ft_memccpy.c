/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:43:03 by agesp             #+#    #+#             */
/*   Updated: 2018/11/08 11:19:32 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c,  size_t n)
{
	int i;
	char *savedst;
	char *savesrc;

	i = 0;
	savedst = (char*)dst;
	savesrc = (char*)src;
	if (n == 0)
		return (dst);
	if (!c)
		return (ft_memcpy(dst, src, n));
	while (i < n && savesrc[i] != c)
	{
		savedst[i] = savesrc[i];
		i++;
	}
	savedst[i] = c;
	dst = savedst;
	return (dst);
}
