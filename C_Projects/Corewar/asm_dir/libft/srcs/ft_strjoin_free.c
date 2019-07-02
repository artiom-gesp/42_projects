/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 18:58:20 by amanuel           #+#    #+#             */
/*   Updated: 2019/04/15 19:49:29 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, char two_bits_free)
{
	char	*s;
	char	*ret;
	char	*old;

	if (!s1 && !s2)
		return (0);
	s = ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	ret = s;
	if ((old = s1))
		while (*old)
			*s++ = *old++;
	if ((old = s2))
		while (*old)
			*s++ = *old++;
	*s = 0;
	if (two_bits_free % 2 && s1)
		free(s1);
	if (two_bits_free / 2 && s2)
		free(s2);
	return (ret);
}
