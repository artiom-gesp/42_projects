/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:21:19 by kecosmon          #+#    #+#             */
/*   Updated: 2019/02/22 15:21:21 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		i2;
	int		lens1;
	char	*str;

	if (s1 && s2)
	{
		i = 0;
		i2 = 0;
		lens1 = ft_strlen(s1);
		str = (char *)malloc(((lens1 + ft_strlen(s2)) + 1) * sizeof(str));
		if (str == NULL)
			return (NULL);
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
		while (s2[i2] != '\0')
			str[i++] = s2[i2++];
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
