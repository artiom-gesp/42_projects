/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:20:44 by kecosmon          #+#    #+#             */
/*   Updated: 2019/02/22 15:20:45 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*strs;
	size_t	lens;

	if (s && f)
	{
		i = 0;
		lens = ft_strlen(s);
		strs = (char *)malloc((lens + 1) * sizeof(*strs));
		if (strs == NULL)
			return (NULL);
		while (s[i] != '\0')
		{
			strs[i] = f(i, s[i]);
			i++;
		}
		strs[i] = '\0';
		return (strs);
	}
	return (NULL);
}
