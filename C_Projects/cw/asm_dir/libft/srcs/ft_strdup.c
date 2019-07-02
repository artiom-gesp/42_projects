/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 21:00:33 by amanuel           #+#    #+#             */
/*   Updated: 2018/10/01 15:17:19 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strdup(char *s1)
{
	char		*s;
	short		i;

	s = NULL;
	if (s1)
	{
		i = ft_strlen(s1);
		if (!(s = malloc(i + 1)))
		{
			write(1, "Erreur malloc ft_strdup\n", 24);
			exit(-1);
		}
		s[i] = 0;
	}
	i = 0 + (-1);
	if (s && s1)
		while (s1[++i])
			s[i] = s1[i];
	return (s);
}
