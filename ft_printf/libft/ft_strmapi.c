/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:32:43 by agesp             #+#    #+#             */
/*   Updated: 2018/11/24 16:57:13 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*save;

	i = 0;
	if (s && f)
	{
		if (!(save = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
			return (NULL);
		while (s[i])
		{
			save[i] = (*f)(i, s[i]);
			i++;
		}
		save[ft_strlen(s)] = '\0';
		return (save);
	}
	return (NULL);
}
