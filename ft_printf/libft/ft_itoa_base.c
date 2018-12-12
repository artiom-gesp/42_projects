/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:15:38 by agesp             #+#    #+#             */
/*   Updated: 2018/11/23 15:00:23 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	is_neg_itoa(int *nb)
{
	*nb *= *nb < 0 ? -1 : 1;
}

static char	*ft_baobab(int nb, int base, int i, int is_neg)
{
	int		save;
	char	*ret;
	char	*el_base;

	save = nb;
	el_base = "0123456789ABCDEF";
	if (base == 10)
		return (ft_itoa(nb));
	is_neg_itoa(&nb);
	while (save /= base)
		i++;
	i += is_neg;
	if (!(ret = malloc(sizeof(char) * i + 2)))
		return (NULL);
	ret[i + 1] = '\0';
	while (nb)
	{
		ret[i] = el_base[nb % base];
		nb /= base;
		i--;
	}
	if (is_neg)
		ret[0] = '-';
	return (ret);
}

char		*ft_itoa_base(int nb, int base)
{
	int		is_neg;
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	is_neg = 0;
	if (nb == 0)
	{
		str = ft_strnew(1);
		str[0] = 0;
		str[1] = '\0';
		return (str);
	}
	return (ft_baobab(nb, base, i, is_neg));
}
