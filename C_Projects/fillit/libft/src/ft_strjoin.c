/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:07:54 by agesp             #+#    #+#             */
/*   Updated: 2018/11/09 15:24:24 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*save;

	i = -1;
	j = -1;
	if (!s1 && s2)
		return (char*)(s2);
	if (s1 && !s2)
		return (char*)(s1);
	if (s1 && s2)
	{
		if (!(save = (char*)malloc(sizeof(char) * (ft_strlen(s1)
							+ ft_strlen(s2) + 1))))
			return (NULL);
		while (s1[++i])
			save[i] = s1[i];
		while (s2[++j])
			save[i++] = s2[j];
		save[i] = '\0';
		return (save);
	}
	return (NULL);
}
