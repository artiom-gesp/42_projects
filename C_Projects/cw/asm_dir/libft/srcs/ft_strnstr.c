/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:58:43 by amanuel           #+#    #+#             */
/*   Updated: 2017/12/06 01:50:12 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *s, char *to_find, int len)
{
	int		i;

	if (!s || !to_find || !*to_find)
		return (0);
	while (*s)
	{
		i = 0;
		while (s[i] == to_find[i] && s[i] && i < len)
			i++;
		if (i == len || !to_find[i])
			return (s);
		s++;
	}
	return (0);
}
