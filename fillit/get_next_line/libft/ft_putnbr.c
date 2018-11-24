/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:26:45 by agesp             #+#    #+#             */
/*   Updated: 2018/11/12 09:39:03 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pow_10(int i)
{
	int		p_10;

	p_10 = 10;
	while (i > 1)
	{
		p_10 *= 10;
		i--;
	}
	p_10 /= 10;
	return (p_10);
}

static void	do_putnbr(int n)
{
	int		i;
	int		save;
	int		p_10;

	save = n;
	i = 0;
	while (save)
	{
		save /= 10;
		i++;
	}
	p_10 = ft_pow_10(i);
	while (i)
	{
		ft_putchar((n / p_10) + '0');
		n %= p_10;
		p_10 /= 10;
		i--;
	}
}

void		ft_putnbr(int n)
{
	long	save;

	save = n;
	if (save == -2147483647)
	{
		ft_putstr("–2147483648");
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		ft_putstr("-");
	}
	if (n == 0)
	{
		ft_putchar('0');
		return ;
	}
	do_putnbr(n);
}
