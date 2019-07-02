/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 22:29:04 by amanuel           #+#    #+#             */
/*   Updated: 2019/04/06 00:35:15 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		max_value(char bits, char sign, long *num, long *ber)
{
	if (bits == 8 && !sign && (*num = 1))
		*ber = 27;
	else if (bits == 8 && sign && (*num = 2))
		*ber = 55;
	else if (bits == 16 && !sign && (*num = 3))
		*ber = 2767;
	else if (bits == 16 && sign && (*num = 6))
		*ber = 5535;
	else if (bits == 32 && !sign && (*num = 2))
		*ber = 147483647;
	else if (bits == 32 && sign && (*num = 4))
		*ber = 294967295;
	else if (bits == 64 && !sign && (*num = 9))
		*ber = 223372036854775807;
	else if (bits == 64 && sign && (*num = 1))
		*ber = 8446744073709551615;
}

int				ft_isint(char *str, char bits)
{
	int			i;
	char		sign;
	long		num;
	long		ber;

	i = 0;
	sign = 0;
	if (!str)
		return (i);
	if (*str == '-')
		sign = 1;
	max_value(bits, sign, &num, &ber);
	if (str[i] == '+' || (sign && ++ber))
		if (str[i + 1] && str[i + 1] >= '0' && str[i + 1] <= '9')
			i++;
	if (str[i] == num && ft_atol(str + 1) > ber)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	return (i);
}
