/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:42:03 by agesp             #+#    #+#             */
/*   Updated: 2018/11/09 11:41:02 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int			i;
	char		*savedst;
	char		*savesrc;

	i = 0;
	savedst = (char*)dst;
	savesrc = (char*)src;
	if (savedst == savesrc)
		return (dst);
	while ((size_t)i < n)
	{
		if (savesrc[i] == savedst[i] &&
				savesrc[ft_strlen(savesrc)] - savedst[0] > 0
				&& (savesrc[0] - savedst[ft_strlen(savedst)]) > 0)
		{
			i = n;
			while (--i >= 0)
				savedst[i] = savesrc[i];
			dst = savedst;
			return (dst);
		}
		i++;
	}
	return (ft_memcpy(dst, src, n));
}
