/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:21:26 by kecosmon          #+#    #+#             */
/*   Updated: 2019/02/22 15:21:28 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	i2;

	i = 0;
	while (i < size && '\0' != dst[i])
		i++;
	if (i == size)
		return (size + ft_strlen(src));
	i2 = 0;
	while ((i + i2 + 1) < size && src[i2] != '\0')
	{
		dst[i + i2] = src[i2];
		i2++;
	}
	dst[i + i2] = '\0';
	if (i + i2 + 1 == size)
	{
		while (src[i2] != '\0')
			i2++;
	}
	return (i + i2);
}
