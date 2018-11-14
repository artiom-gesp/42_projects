/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:50:29 by agesp             #+#    #+#             */
/*   Updated: 2018/11/09 15:07:20 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*save;

	i = start;
	j = 0;
	if (s)
	{
		if (!(save = (char*)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		while ((size_t)j < len)
		{
			save[j] = s[i];
			i++;
			j++;
		}
		save[len] = '\0';
		return (save);
	}
	return (NULL);
}
