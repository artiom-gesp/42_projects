/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 12:16:43 by agesp             #+#    #+#             */
/*   Updated: 2018/11/07 10:45:51 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	int				save;

	i = 0;
	save = 0;
	while (i < n)
	{
		if (s1[i] == s2[i])
		{
			i++;
		}
		else
		{
			save = s1[i] - s2[i];
			i = n;
		}
	}
	return (save);
}
