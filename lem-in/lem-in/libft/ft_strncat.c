/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:20:52 by kecosmon          #+#    #+#             */
/*   Updated: 2019/02/22 15:20:52 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		lens1;

	i = 0;
	lens1 = ft_strlen(s1);
	while (s2[i] != '\0' && i < n)
	{
		s1[lens1 + i] = s2[i];
		i++;
	}
	s1[lens1 + i] = '\0';
	return (s1);
}
