/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 18:58:20 by amanuel           #+#    #+#             */
/*   Updated: 2019/04/15 19:49:16 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin_free(char *s1, char *s2, short i, char two_bits_free)
{
	char	*s;
	char	*ret;
	char	*old;

	if (!s1 && !s2)
		return (0);
	s = (char*)ft_memalloc(i + 1);
	ret = s;
	if ((old = s1))
		while (*old && i && i--)
			*s++ = *old++;
	if ((old = s2))
		while (*old && i && i--)
			*s++ = *old++;
	*s = 0;
	if (two_bits_free % 2 && s1)
		free(s1);
	if (two_bits_free / 2 && s2)
		free(s2);
	return (ret);
}
