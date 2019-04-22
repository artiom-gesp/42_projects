/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:21:51 by kecosmon          #+#    #+#             */
/*   Updated: 2019/02/22 15:21:52 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_secure(const char *s)
{
	if (s == NULL)
		return (0);
	else
		return (ft_strlen(s));
}

char	*ft_strdup(const char *s1)
{
	char	*duplicate;
	int		strlen;
	int		j;

	strlen = ft_strlen_secure(s1);
	j = 0;
	duplicate = (char *)malloc(((unsigned long)strlen + 1) * sizeof(char));
	if (duplicate == NULL)
		return (NULL);
	while (s1[j] != '\0')
	{
		duplicate[j] = s1[j];
		j++;
	}
	duplicate[j] = '\0';
	return (duplicate);
}
