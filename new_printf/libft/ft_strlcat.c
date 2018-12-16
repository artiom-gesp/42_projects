/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 14:39:28 by agesp             #+#    #+#             */
/*   Updated: 2018/11/24 17:10:27 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	a;
	size_t	b;

	i = 0;
	a = ft_strlen(dst);
	b = ft_strlen(src);
	if (!size)
		return (b);
	if (size < a)
		return (b + size);
	while (a + i < size - 1 && i < b)
	{
		dst[a + i] = src[i];
		i++;
	}
	dst[a + i] = '\0';
	return (a + b);
}
