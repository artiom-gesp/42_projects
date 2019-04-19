/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:08:47 by agesp             #+#    #+#             */
/*   Updated: 2018/11/24 17:18:57 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	j;
	size_t	k;

	j = 0;
	if (needle[0] == '\0')
		return (char*)(haystack);
	if (haystack[0] == '\0')
		return (0);
	if (!len)
		return (NULL);
	while (haystack[j] != '\0')
	{
		k = 0;
		while (needle[k] == haystack[j + k] && j + k < len)
		{
			k++;
			if (!needle[k])
				return (char*)&haystack[j];
		}
		j++;
	}
	return (0);
}
