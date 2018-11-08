/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:08:47 by agesp             #+#    #+#             */
/*   Updated: 2018/11/07 14:07:15 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	getlo(const char *c, const char *n)
{
	int i;

	i = 0;
	while (c[i] == n[i])
		i++;
	return (i);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int j;
	int k;

	j = 0;
	if (needle[0] == '\0')
		return (char *)(haystack);
	if (haystack[0] == '\0')
		return (0);
	if (ft_strlen(haystack) == ft_strlen(needle))
		if (getlo(haystack, needle) - 1 == ft_strlen(needle))
			if (len < ft_strlen(haystack))
				return (0);
	while (haystack[j] != '\0' && j < len - ft_strlen(needle) + 1)
	{
		k = 0;
		while (needle[k] != '\0' && needle[k] == haystack[j + k])
		{
			k++;
			if (!needle[k])
				return (char*)&haystack[j];
		}
		j++;
	}
	return (0);
}
