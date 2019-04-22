/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:26:19 by kecosmon          #+#    #+#             */
/*   Updated: 2019/02/22 15:26:21 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_isnegative(int *n, int *neg)
{
	if (*n < 0)
	{
		*n *= -1;
		*neg = 1;
	}
}

int		ft_lennb(int nb)
{
	int i;

	i = 2;
	while (nb >= 10)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		len;
	int		neg;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = n;
	neg = 0;
	ft_isnegative(&n, &neg);
	len = ft_lennb(n);
	len = len + neg;
	if ((s = (char*)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	s[--len] = '\0';
	while (len--)
	{
		s[len] = n % 10 + '0';
		n = n / 10;
	}
	if (neg)
		s[0] = '-';
	return (s);
}
