/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:41:48 by agesp             #+#    #+#             */
/*   Updated: 2018/11/09 11:39:34 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*savedst;
	unsigned char	*savesrc;

	i = 0;
	savedst = (unsigned char*)dst;
	savesrc = (unsigned char*)src;
	if (savedst == savesrc)
		return (dst);
	while (i < n)
	{
		savedst[i] = savesrc[i];
		i++;
	}
	dst = savedst;
	return (dst);
}
