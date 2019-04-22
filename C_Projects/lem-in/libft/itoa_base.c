/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:42:35 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/05 13:48:08 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/includes/printf.h"

static int	ft_pow(uintmax_t value, int base)
{
	uintmax_t nb;

	nb = 1;
	while (value >= (uintmax_t)base)
	{
		value /= base;
		nb++;
	}
	return (nb);
}

static void	ft_itoa_check(intmax_t *value, int base, int *neg)
{
	if (*value < 0)
	{
		if (base == 10)
			*neg = 1;
		*value *= -1;
	}
}

char		*ft_itoa_base(intmax_t value, int base, t_parsing *lst)
{
	char	*str;
	int		i;
	int		neg;

	neg = 0;
	i = 1;
	if (base == 10 && value < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	ft_itoa_check(&value, base, &neg);
	i = ft_pow(value, base);
	str = ft_strnew(i);
	str[i + neg] = '\0';
	while (i-- > 0)
	{
		if (lst->conv == 'X')
			str[i + neg] = (value % base) + (value % base > 9 ? 'A' - 10 : '0');
		else
			str[i + neg] = (value % base) + (value % base > 9 ? 'a' - 10 : '0');
		value = value / base;
	}
	if (neg)
		str[0] = '-';
	return (str);
}

char		*ft_uitoa_base(uintmax_t value, int base, t_parsing *lst)
{
	char	*str;
	int		i;

	i = 1;
	i = ft_pow(value, base);
	str = ft_strnew(i);
	str[i] = '\0';
	while (i-- > 0)
	{
		if (lst->conv == 'X')
			str[i] = (value % base) + (value % base > 9 ? 'A' - 10 : '0');
		else
			str[i] = (value % base) + (value % base > 9 ? 'a' - 10 : '0');
		value = value / base;
	}
	return (str);
}
