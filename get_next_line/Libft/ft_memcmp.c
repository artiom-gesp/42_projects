/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:32:03 by agesp             #+#    #+#             */
/*   Updated: 2018/11/09 11:25:19 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*saves1;
	unsigned char	*saves2;

	i = 0;
	saves1 = (unsigned char*)s1;
	saves2 = (unsigned char*)s2;
	while (i < n && saves1[i] == saves2[i])
	{
		i++;
	}
	if (i == n)
		return (0);
	return (saves1[i] - saves2[i]);
}
