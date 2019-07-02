/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imaxtoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 19:13:49 by amanuel           #+#    #+#             */
/*   Updated: 2018/12/27 16:21:18 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_mall_size(long n)
{
	short		i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n && ++i)
		n = n / 10;
	return (i);
}

char			*ft_ltoa(long n)
{
	char		*s;
	short		j;

	j = ft_mall_size(n);
	if (!(s = malloc(j + 1)))
	{
		write(1, "Erreur malloc ft_imaxtoa\n", 24);
		exit(-1);
	}
	s[j] = 0;
	if (n == 0)
		*s = '0';
	else if (n < 0)
	{
		*s = '-';
		s[--j] = -(n % 10) + '0';
		n = n / 10;
		n = -n;
	}
	while (n && j >= 0)
	{
		s[--j] = n % 10 + '0';
		n = n / 10;
	}
	return (s);
}
