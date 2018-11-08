/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:32:03 by agesp             #+#    #+#             */
/*   Updated: 2018/11/08 13:15:08 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int i;
	char *saves1;
	char *saves2;

	i = 0;
	saves1 = (char*)s1;
	saves2 = (char*)s2;

	if (saves1[0] == '\0'  && saves2[0] == '\0')
	{
		if (n == 1 || n == 0)
			return (0);
		return (-1);
	}
	if (ft_strlen(s1) + 1 < n)
		return (1);
	while (i < n)
	{
		if ((unsigned char)saves1[i] == (unsigned char)saves2[i])
			i++;
		return ((unsigned char)saves1[i] - (unsigned char)saves2[i]);
	}
	return (0);
}
