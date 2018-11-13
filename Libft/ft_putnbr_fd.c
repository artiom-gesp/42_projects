/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:39:10 by agesp             #+#    #+#             */
/*   Updated: 2018/11/12 09:39:41 by agesp            ###   ########.fr       */
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

static void	do_putnbr(int n, int fd)
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
		ft_putchar_fd((n / p_10) + '0', fd);
		n %= p_10;
		p_10 /= 10;
		i--;
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	long	save;

	save = n;
	if (save == -2147483647)
	{
		ft_putstr_fd("–2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		ft_putstr_fd("-", fd);
	}
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	do_putnbr(n, fd);
}
