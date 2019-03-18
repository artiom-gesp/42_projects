/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:19:56 by kecosmon          #+#    #+#             */
/*   Updated: 2019/02/22 15:19:57 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*strs;
	char	cc;
	char	*fin;

	i = 0;
	strs = (char *)s;
	cc = (char)c;
	fin = NULL;
	while (s[i] != '\0')
	{
		if (strs[i] == cc)
			fin = &strs[i];
		i++;
	}
	if (cc == '\0')
		return (&strs[i]);
	return (fin);
}
