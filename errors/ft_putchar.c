/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:25:40 by agesp             #+#    #+#             */
/*   Updated: 2018/12/18 13:15:33 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		get_nb_bits(char *ret)
{
	int		bits;
	int		ones;
	int		zeroes;
	int		i;

	bits = 16;
	ones = 0;
	zeroes = 0;
	i = 0;
	while (ret[i] && ret[i] == '0')
	{
		i++;
		bits--;
	}
	return (bits);
}

void	ft_put_three(char *ret, char *retun, unsigned char digit, char *save)
{
	retun = ret;
	ft_strcpy(save, "1110");
	ft_strncat(save, ret, 4);
	digit = ft_atoi_base(save, 2);
	ret = ft_itoa_base(digit, 16, 'a');
	digit = ft_atoi_base(ret, 16);
	write(1, &digit, 1);
	ft_bzero(save, 9);
	ft_strcpy(save, "10");
	ft_strncat(save, retun + 5, 6);
	digit = ft_atoi_base(save, 2);
	ret = ft_itoa_base(digit, 16, 'a');
	digit = ft_atoi_base(ret, 16);
	write(1, &digit, 1);
	ft_bzero(save, 9);
	ft_strcpy(save, "10");
	ft_strncat(save, retun + 9, 6);
	digit = ft_atoi_base(save, 2);
	ret = ft_itoa_base(digit, 16, 'a');
	digit = ft_atoi_base(ret, 16);
	write(1, &digit, 1);
	digit = 0x0a;
	write(1, &digit, 1);
}

void	ft_put_two(char *ret, char *save)
{
	unsigned char	digit;
	char			*retun;

	retun = ret;
	ft_strcpy(save, "110");
	ft_strncat(save, ret + 5, 5);
	digit = ft_atoi_base(save, 2);
	ret = ft_itoa_base(digit, 16, 'a');
	digit = ft_atoi_base(ret, 16);
	write(1, &digit, 1);
	ft_bzero(save, 9);
	ft_strcpy(save, "10");
	ft_strncat(save, retun + 10, 6);
	digit = ft_atoi_base(save, 2);
	ret = ft_itoa_base(digit, 16, 'a');
	digit = ft_atoi_base(ret, 16);
	write(1, &digit, 1);
	digit = 0x0a;
	write(1, &digit, 1);
}

void	ft_putchar(unsigned int c)
{
	char	*save;
	char	*ret;
	char	*retun;
	int		bits;
	int		digit;

	digit = 0;
	ret = get_bits(c);
	retun = ret;
	bits = get_nb_bits(ret);
	if (bits < 8)
		write(1, &c, 1);
	else
	{
		if (!(save = malloc(sizeof(char) * 9)))
			return ;
		save[8] = '\0';
		if (bits > 7 && bits < 11)
			ft_put_two(ret, save);
		if (bits > 10 && bits < 17)
			ft_put_three(ret, retun, digit, save);
		free(save);
	}
}
