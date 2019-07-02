/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itochar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 19:13:49 by amanuel           #+#    #+#             */
/*   Updated: 2019/04/15 19:59:43 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			ft(int *n, unsigned short strt, char pt, short stop)
{
	short			c;

	if (strt == 32 || strt == 2048)
		c = 128;
	else if (strt == 1024)
		c = 192;
	else
		c = 224;
	while (*n >= stop)
	{
		if (*n >= strt)
		{
			c += pt;
			*n -= strt;
		}
		strt /= 2;
		pt /= 2;
	}
	return (c);
}

static char			*ft_settings(int n)
{
	char			*buff;

	buff = NULL;
	if (n < 256)
		buff = ft_lilstr(n, 0, 0);
	else if (n < 2048)
		buff = ft_lilstr(ft(&n, 1024, 16, 64), ft(&n, 32, 32, 1), 0);
	else if (n < 65536)
		buff = ft_lilstr(ft(&n, 32768, 8, 4096),
				ft(&n, 2048, 32, 64), ft(&n, 32, 32, 1));
	else
	{
		write(1, "int trop gros pour itochar\n", 27);
		exit(-1);
	}
	return (buff);
}

char				*ft_itostr(int *n, int m)
{
	char			*s;

	s = NULL;
	if (n)
	{
		while (*n)
		{
			s = ft_strjoin_free(s, ft_settings(*n), 3);
			n++;
		}
	}
	else if (m)
		s = ft_settings(m);
	else
		s = ft_strdup("(null)");
	return (s);
}
