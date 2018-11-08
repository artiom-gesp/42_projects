/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:21:03 by agesp             #+#    #+#             */
/*   Updated: 2018/11/08 12:19:01 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int i;
	unsigned char *save;

	i = 0;
	save = (unsigned char*)(s);
	while (i < n)
	{
		if (save[i] == (unsigned char)c)
			return (&save[i]);
		i++;
	}
	return (NULL);
}
