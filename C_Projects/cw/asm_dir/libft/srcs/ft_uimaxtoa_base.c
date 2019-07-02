/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 19:13:49 by amanuel           #+#    #+#             */
/*   Updated: 2018/12/27 16:19:35 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_mall_size(uintmax_t n, char base)
{
	int		i;

	i = 0;
	if (n == 0)
		i++;
	while (n && ++i)
		n = n / base;
	return (i);
}

char			*ft_uimaxtoa_base(uintmax_t n, char base)
{
	char		*s;
	char		c;
	char		uppercase;
	int			j;

	if (!(uppercase = 0) && base < 0 && ++uppercase)
		base = -base;
	j = ft_mall_size(n, base);
	s = ft_strnew(j);
	if (n == 0)
		*s = '0';
	while (n && j >= 0)
	{
		if ((c = n % base + '0') > '9')
		{
			if (!uppercase)
				c = 'a' + c - '0' - 10;
			else
				c = 'A' + c - '0' - 10;
		}
		s[--j] = c;
		n = n / base;
	}
	return (s);
}
