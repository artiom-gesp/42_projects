/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 12:16:43 by agesp             #+#    #+#             */
/*   Updated: 2018/11/09 11:34:09 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	int				save;

	i = 0;
	save = 0;
	if (s1[i] && !s2[i])
		return (1);
	if (!s1[i] && s2[i])
		return (-1);
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
		{
			i++;
		}
		else
		{
			save = ((unsigned char)s1[i] - (unsigned char)s2[i]);
			i = n;
		}
	}
	return (save);
}
