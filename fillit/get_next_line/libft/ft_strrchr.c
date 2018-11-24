/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 11:34:57 by agesp             #+#    #+#             */
/*   Updated: 2018/11/09 11:35:22 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*z;

	i = 0;
	z = "";
	if (c == '\0')
	{
		while (s[i])
			i++;
		return (char*)(&s[i]);
	}
	while (s[i])
		i++;
	while (i > 0)
	{
		if (s[i] == (char)(c))
			return (char*)&s[i];
		i--;
	}
	return (0);
}