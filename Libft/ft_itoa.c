/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:40:10 by agesp             #+#    #+#             */
/*   Updated: 2018/11/12 09:41:32 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	is_neg_itoa(int *n, int *negative)
{
	if (*n < 0)
	{
		*n *= -1;
		*negative = 1;
	}
}

static char	*get_int_min(void)
{
	int		i;
	char	*int_min;
	char	*my_return;

	i = 0;
	int_min = "-2147483648";
	my_return = (char*)malloc(sizeof(char) * 12);
	while (int_min[i])
	{
		my_return[i] = int_min[i];
		i++;
	}
	my_return[11] = '\0';
	return (my_return);
}

char		*ft_itoa(int n)
{
	int		save;
	int		i;
	int		is_neg;
	char	*my_return;

	if (n == -2147483648)
		return (get_int_min());
	save = n;
	i = 2;
	is_neg = 0;
	is_neg_itoa(&n, &is_neg);
	while (save /= 10)
		i++;
	i += is_neg;
	if (!(my_return = (char*)malloc(sizeof(char) * i)))
		return (NULL);
	my_return[--i] = '\0';
	while (i--)
	{
		my_return[i] = n % 10 + '0';
		n = n / 10;
	}
	if (is_neg)
		my_return[0] = '-';
	return (my_return);
}
