/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramsum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 13:23:29 by agesp             #+#    #+#             */
/*   Updated: 2019/01/07 15:49:22 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	mini_putnbr(int nbr)
{
	if (nbr > 9)
		mini_putnbr(nbr / 10);
	ft_putchar(nbr % 10 + 48);
}

int		main(int ac, char **av)
{
	(void)av;
	mini_putnbr(ac - 1);
	write(1, "\n", 1);
	return (0);
}
