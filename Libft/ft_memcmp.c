/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:32:03 by agesp             #+#    #+#             */
/*   Updated: 2018/11/08 17:27:56 by agesp            ###   ########.fr       */
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

	if (saves1[i] && !saves2[i])
		return (1);
	if (!saves1[i] && saves2[i])
		return (-1);
	while (i < n && saves1[i] && saves2[i])
	{
		if (saves1[i] == saves2[i])
			i++;
		else
			return (saves1[i] - saves2[i]);
	}
	return (0);
}
