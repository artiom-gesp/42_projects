/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:43:42 by agesp             #+#    #+#             */
/*   Updated: 2018/11/12 10:48:39 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_biggest(char const *s1, char const *s2)
{
	if (ft_strlen(s1) >= ft_strlen(s2))
		return (ft_strlen(s1));
	else
		return (ft_strlen(s2));
}

int				ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t		i;

	i = 0;
	if (!s1 && !s2)
		return (1);
	if (s1 && s2)
	{
		if (n > ft_strlen(s1) && n > ft_strlen(s2))
			n = get_biggest(s1, s2);
		if (!s1[i] && !s2[i])
			return (1);
		while (s1[i] && s2[i] && i < n)
		{
			if (s1[i] == s2[i])
				i++;
			else
				return (0);
		}
		if (i == n)
			return (1);
	}
	return (0);
}
