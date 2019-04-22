/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:19:52 by agesp             #+#    #+#             */
/*   Updated: 2018/11/12 16:20:00 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int			i;
	char		*save_dst;
	char		*save_src;

	i = 0;
	save_dst = (char*)dst;
	save_src = (char*)src;
	if (save_dst == save_src)
		return (dst);
	while ((size_t)i < n)
	{
		if (dst > src)
		{
			i = n;
			while (--i >= 0)
				save_dst[i] = save_src[i];
			dst = save_dst;
			return (dst);
		}
		i++;
	}
	return (ft_memcpy(dst, src, n));
}
