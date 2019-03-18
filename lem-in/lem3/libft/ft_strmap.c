/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:21:11 by kecosmon          #+#    #+#             */
/*   Updated: 2019/02/22 15:21:13 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
			strs[i] = f(s[i]);
			i++;
		}
		return (strs);
	}
	return (NULL);
}
