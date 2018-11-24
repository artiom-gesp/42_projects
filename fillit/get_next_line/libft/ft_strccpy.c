/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:29:25 by agesp             #+#    #+#             */
/*   Updated: 2018/11/20 14:36:11 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strccpy(char *dst, const char *src, int c)
{
	int i;

	i = 0;
	while (src[i] && dst[i])
	{
		if (src[i] == c)
		{
			dst[i] = '\0';
			return (dst);
		}
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
