/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_minus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 12:13:46 by agesp             #+#    #+#             */
/*   Updated: 2019/02/11 13:11:14 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_plus(t_plist *list, int len, int plus, char *ret)
{
	int i;
	int	lim;

	i = -1;
	lim = list->min_width + list->precision < len ? 0
		: list->min_width - list->precision;
	if (list->precision > len && list->precision > list->min_width)
	{
		ft_putchar(plus);
		ft_putstr(ret);
	}
	lim--;
	while (++i < (lim = list->precision > len
				? lim : list->min_width - len - 1))
		ft_putchar(' ');
	return (i);
}

void	print_minus_wd(t_plist *list, char *ret, int plus, int len)
{
	int	i;
	int	lim;

	i = -1;
	lim = list->min_width + list->precision < len ? 0
		: list->min_width - list->precision;
	if (plus && list->min_width > len && is_int(list->flag))
		i = print_plus(list, len, plus, ret);
	else if ((!plus || !is_int(list->flag)) && (list->min_width - len) > 0)
	{
		if (list->precision > len && list->precision > list->min_width)
			ft_putstr(ret);
		while (++i < (lim = list->precision > len
					? lim : list->min_width - len))
			ft_putchar(' ');
	}
	else if (list->precision > len)
		ft_putstr(ret);
	list->size += list->precision > len ? i : len + i;
}

void	print_pw_minus(t_plist *list, char *ret)
{
	int	plus;
	int len;

	len = (int)ft_strlen(ret);
	plus = 0;
	plus = ft_strchr(list->sign, ' ')
		&& ret[0] != '-' && is_int(list->flag) ? ' ' : 0;
	plus = ft_strchr(list->sign, '+')
		&& ret[0] != '-' && is_int(list->flag) ? '+' : plus;
	if (list->precision <= len && list->min_width <= len)
	{
		plus ? ft_putchar(plus) : do_nothing();
		print_hash(list, ret);
		ft_putstr(ret);
		plus = plus ? 1 : 0;
		list->size += (len + plus);
	}
	else if (list->min_width > len)
	{
		print_precision(list, ret, 0);
		print_minus_wd(list, ret, plus, len);
	}
}
