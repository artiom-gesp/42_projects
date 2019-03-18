/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:26:19 by kecosmon          #+#    #+#             */
/*   Updated: 2019/02/22 15:26:21 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	int					i2;
	unsigned char		uc;
	char				*strdst;
	unsigned const char	*strsrc;

	i = 0;
	i2 = 0;
	uc = c;
	strdst = dst;
	strsrc = src;
	while (i < n)
	{
		strdst[i] = strsrc[i];
		if (strsrc[i] == uc)
			return (&dst[i + 1]);
		i++;
	}
	return (NULL);
}
