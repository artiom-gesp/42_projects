/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 15:51:11 by agesp             #+#    #+#             */
/*   Updated: 2019/01/07 16:21:14 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int		nbr_len(int nbr, int base)
{
	int i;

	i = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		i++;
	}
	if (nbr == 0)
		return (1);
	while (nbr)
	{
		nbr /= base;
		i++;
	}
	return (i);
}

char	*ft_itoa_base(int nbr, int base)
{
	int		i;
	int		is_neg;
	char	*ret;

	is_neg = nbr < 0 && base == 10 ? 1 : 0;
	nbr *= nbr < 0 ? -1 : 1;
	if (nbr == -2147483648)
		return ("-2147483648");
	i = nbr_len(nbr, base);
	if (!(ret = malloc(sizeof(char) * i + is_neg)))
		return (NULL);
	ret[i + is_neg] = '\0';
	while (i-- > 0)
	{
		ret[i + is_neg] = (nbr % base) + (nbr % base > 9 ? 'A' - 10 : '0');
		nbr /= base;
	}
	if (is_neg)
		ret[0] = '-';
	return (ret);
}

int		main(int ac, char **av)
{
	printf("%s\n", ft_itoa_base(atoi(av[1]), atoi(av[2])));
}
