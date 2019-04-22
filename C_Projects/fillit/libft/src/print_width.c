/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 12:23:18 by agesp             #+#    #+#             */
/*   Updated: 2019/02/11 13:25:42 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_wp(t_plist *list, int len, char *ret)
{
	int		i;
	int		lim;
	int		flag;

	i = -1;
	print_sign(list, ret, 0);
	list->precision = list->precision == -1 ? 0 : list->precision;
	flag = list->min_width + list->precision < len
		? 0 : (list->min_width - list->precision);
	lim = list->min_width > list->precision
		? flag : 0;
	flag = ret[0] == '-' ? 1 : 0;
	i += list->precision >= len ? flag : 0;
	if (lim > 0 && list->min_width - len > 0)
		while (++i < (lim = list->precision > len
					? lim : list->min_width - len))
			ft_strchr(list->sign, '0')
				&& list->precision == 0 ? ft_putchar('0') : ft_putchar(' ');
	print_sign(list, ret, 1);
	list->size = i == -1 ? list->size + 0 : list->size + i;
	lim = list->precision + flag - len;
	i = print_zero(lim);
	list->size = i == -1 ? list->size + 0 : list->size + i;
	return (flag == 1 ? (1) : (0));
}

void	print_hash_sign(t_plist *list, int flag, int len, int hash)
{
	if ((!flag && ft_strchr(list->sign, '0'))
			|| (flag && !ft_strchr(list->sign, '0')))
	{
		if (hash && list->flag == 'o')
		{
			list->precision <= len ? ft_putchar('0') : ft_putchar(' ');
			list->size++;
		}
		else if ((hash && (list->flag == 'x' || list->flag == 'X'))
				|| list->flag == 'p')
		{
			list->size += 2;
			ft_putchar('0');
			ft_putchar(list->flag != 'p' ? list->flag : 'x');
		}
	}
}

void	print_wp_x(t_plist *list, int len, int hash)
{
	int		i;
	int		lim;
	int		flag;

	i = -1;
	print_hash_sign(list, 0, len, hash);
	list->precision = list->precision == -1 ? 0 : list->precision;
	flag = list->min_width + list->precision < len
		? 0 : (list->min_width - list->precision);
	lim = list->min_width > list->precision
		? flag : 0;
	if (lim > 0 && list->min_width - len > 0)
		while (++i < (lim = list->precision > len
					? lim : list->min_width - len))
			ft_strchr(list->sign, '0')
				&& list->precision == 0 ? ft_putchar('0') : ft_putchar(' ');
	print_hash_sign(list, 1, len, hash);
	list->size = i == -1 ? list->size + 0 : list->size + i;
	i = -1;
	lim = list->precision - len;
	i = print_zero(lim);
	list->size = i == -1 ? list->size + 0 : list->size + i;
}

void	print_width(t_plist *list, int len)
{
	int		i;

	i = -1;
	if (list->min_width > len)
		while (++i < list->min_width - len)
			ft_putchar(' ');
	list->size = i == -1 ? list->size + 0 : list->size + i;
}
