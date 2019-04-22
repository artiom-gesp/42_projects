/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:25:09 by kecosmon          #+#    #+#             */
/*   Updated: 2019/02/22 15:25:12 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*strs;
	char	cc;

	i = 0;
	strs = (char *)s;
	cc = (char)c;
	while (strs[i] != '\0')
	{
		if (strs[i] == cc)
			return (&strs[i]);
		i++;
	}
	if (cc == '\0')
		return (&strs[i]);
	return (NULL);
}
