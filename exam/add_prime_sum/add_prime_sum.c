/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_prime_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 13:31:15 by agesp             #+#    #+#             */
/*   Updated: 2019/01/07 13:58:16 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		is_prime(int prime)
{
	int save;

	save = prime - 1;
	if (prime == 1)
		return (0);
	while (save > 1)
	{
		if (prime % save == 0)
			return (0);
		save--;
	}
	return (1);
}

int		mini_atoi(char *str)
{
	int i;
	int	ret;

	i = 0;
	ret = 0;
	if (str[i] == '-')
		return (0);
	while (str[i])
	{
		ret *= 10;
		ret += (str[i] - 48);
		i++;
	}
	return (ret);
}

void	mini_putnbr(int nbr)
{
	int c;

	c = 0;
	if (nbr >= 0)
	{
		if (nbr > 9)
			mini_putnbr(nbr / 10);
		c = nbr % 10 + 48;
		write(1, &c, 1);
	}
}

int		main(int ac, char **av)
{
	int	prime;
	int	print;

	print = 0;
	if (ac == 2 && (prime = mini_atoi(av[1])))
	{
		while (prime)
		{
			if (is_prime(prime))
				print += prime;
			prime--;
		}
		mini_putnbr(print);
	}
	else
		write(1, "0", 1);
	write(1, "\n", 1);
	return (0);
}
