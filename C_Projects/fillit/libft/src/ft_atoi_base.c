/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:00:36 by agesp             #+#    #+#             */
/*   Updated: 2018/11/23 11:09:10 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	do_base(char c, int base)
{
	int		i;
	char	*base1;
	char	*base2;

	i = 0;
	base1 = "0123456789ABCDEF";
	base2 = "0123456789abcdef";
	while (i < base)
	{
		if (c == base1[i] || c == base2[i])
			return (i);
		i++;
	}
	return (-1);
}

int			ft_atoi_base(char *nbr, int base)
{
	int i;
	int is_neg;
	int ret;

	i = 0;
	ret = 0;
	is_neg = 0;
	while (ft_isspace(nbr[i]))
		i++;
	if (nbr[i] == '+' || nbr[i] == '-')
	{
		if (nbr[i] == '-')
			is_neg = 1;
		i++;
	}
	while (do_base(nbr[i], base) != -1)
	{
		ret *= base;
		ret += do_base(nbr[i], base);
		i++;
	}
	if (is_neg)
		return (-ret);
	return (ret);
}
