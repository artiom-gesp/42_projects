/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:18:53 by kecosmon          #+#    #+#             */
/*   Updated: 2019/02/22 15:18:54 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	unsigned int	tempstart;
	char			*troncs;

	if (s)
	{
		i = 0;
		tempstart = start;
		troncs = (char *)malloc((len + 1) * sizeof(troncs));
		if (troncs == NULL)
			return (NULL);
		while (i < len)
		{
			troncs[i] = s[tempstart];
			i++;
			tempstart++;
		}
		troncs[i] = '\0';
		return (troncs);
	}
	return (NULL);
}
