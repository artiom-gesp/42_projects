/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:49:34 by amanuel           #+#    #+#             */
/*   Updated: 2018/06/09 02:22:20 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, char *src, int len)
{
	int		i;

	i = 0 + (-1);
	if (src)
	{
		len++;
		while (--len && src[++i])
			dst[i] = src[i];
		len++;
		while (--len)
			dst[i++] = '\0';
	}
	return (dst);
}
