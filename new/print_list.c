/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 10:16:09 by agesp             #+#    #+#             */
/*   Updated: 2018/12/21 17:52:51 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*convert_dioux(char flag, va_list *ap, int base, int conv)
{
	char *ret;

	ret = NULL;
	if (conv == 2 && flag == 'u')
		ret = get_u((unsigned long long )va_arg(*ap, long long), base, flag - 23);
	else if (conv == 2)
		ret = ft_itoa_base(va_arg(*ap, long long), base, flag - 23);
	else if (conv == 1 && flag == 'u')
		ret = get_u((unsigned long)va_arg(*ap, uintmax_t), base, flag - 23);
	else if (conv == 1)
		ret = ft_itoa_base(va_arg(*ap, long), base, flag - 23);
	else if (conv == 3 && (flag == 'd' || flag == 'i'))
		ret = ft_itoa_base((short int)va_arg(*ap, int), base, flag - 23);
	else if (conv == 3)
		ret = ft_itoa_base((unsigned short int)va_arg(*ap, int), base, flag - 23);
	else if (conv == 4 && (flag == 'd' || flag == 'i'))
		ret = ft_itoa_base((char)va_arg(*ap, int), base, flag - 23);
	else if (conv == 4)
		ret = ft_itoa_base((unsigned char)va_arg(*ap, int), base, flag - 23);
	else if (flag == 'd' || flag == 'i')
		ret = ft_itoa_base(va_arg(*ap, int), base, flag - 23);
	else if (flag == 'u')
		ret = ft_itoa_base((unsigned int)va_arg(*ap, long long), base, flag - 23);
	else if (flag == 'o' || flag == 'u' || flag == 'x' || flag == 'X')
		ret = ft_itoa_base(va_arg(*ap, unsigned int), base, flag - 23);
	return (ret);
}

int	add_start(t_plist *list)
{
	if (ft_strchr(list->sign, '+') || ft_strchr(list->sign, ' '))
		return (1);
	return (0);
}

void	print_sign(t_plist *list, char *ret, int flag)
{
	int	len;

	len = (int)ft_strlen(ret);
	if (list->flag == 'd' || list->flag == 'i')
	{
	if ((!flag && ft_strchr(list->sign, '0')) || (flag && !ft_strchr(list->sign, '0')))
	{
		if (ret[0] == '-')
		{
			ft_putchar('-');
			list->size += list->precision < len ? 1 : 0;
		}
		else if (ft_strchr(list->sign, '+'))
		{
			list->size++;
			ft_putchar('+');

		}
		else if (ft_strchr(list->sign, ' '))
		{
			ft_putchar(' ');
			list->size++;
		}
	}
	if (!flag && add_start(list) && ret[0] != '-')
		list->min_width--;
	}
}

int		print_wp(t_plist *list, int len, char *ret)
{
	int		i;
	int		lim;
	int		flag;

	i = -1;
		print_sign(list, ret, 0);
	list->precision = list->precision == -1 ? 0 : list->precision;
	flag = list->min_width + list->precision < len ?
		0 : (list->min_width - list->precision);
	lim = list->min_width > list->precision ?
		flag : 0;
	flag = ret[0] == '-' ? 1 : 0;
	i += list->precision >= len ? flag : 0;
	if (lim > 0 && list->min_width - len > 0)
		while (++i < (lim = list->precision > len ? lim: list->min_width - len))
			ft_strchr(list->sign, '0') && list->precision == 0 ? ft_putchar('0') : ft_putchar(' ');
		print_sign(list, ret, 1);
	list->size = i == -1 ? list->size + 0 : list->size + i;
	i = -1;
	lim = list->precision + flag - len;
	if (lim > 0)
		while (++i < lim)
			ft_putchar('0');
	list->size = i == -1 ? list->size + 0 : list->size + i;
	return flag == 1 ? 1 : 0;
}

void	print_hash_sign(t_plist *list, int flag, int len, int hash)
{
	if ((!flag && ft_strchr(list->sign, '0'))
		|| (flag && !ft_strchr(list->sign, '0')))
	{
		if (hash && list->flag == 'o')
		{
			list->precision <= len ? ft_putchar('0') : ft_putchar(' ');;
			list->size++;
		}
		else if (hash && (list->flag == 'x' || list->flag == 'X'))
		{
			list->size += 2;
			ft_putchar('0');
			ft_putchar(list->flag);
		}
	}
}

void		print_wp_x(t_plist *list, int len, int hash)
{
	int		i;
	int		lim;
	int		flag;

	i = -1;
	print_hash_sign(list, 0, len, hash);
	list->precision = list->precision == -1 ? 0 : list->precision;
	flag = list->min_width + list->precision < len ?
		0 : (list->min_width - list->precision);
	lim = list->min_width > list->precision ?
		flag : 0;
	if (lim > 0 && list->min_width - len > 0)
		while (++i < (lim = list->precision > len ? lim: list->min_width - len))
			ft_strchr(list->sign, '0') && list->precision == 0 ? ft_putchar('0') : ft_putchar(' ');
	print_hash_sign(list, 1, len, hash);
	list->size = i == -1 ? list->size + 0 : list->size + i;
	i = -1;
	lim = list->precision - len;
	if (lim > 0)
		while (++i < lim)
			ft_putchar('0');
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



int	print_list(t_plist *list, va_list *ap)
{
	if (list->flag == 'd' || list->flag == 'i')
		integer_print(list, ap);
	if (list->flag == 'o')
		print_o(list, ap);
	if (list->flag == 'u')
		print_u(list, ap);
	if (list->flag == 'x' || list->flag == 'X')
		print_x(list, ap);
	if (list->flag == 'c')
		print_c(list, ap);
	if (list->flag == 's')
		print_s(list, ap);
	if (list->flag == '%')
		print_percent(list);
	if (list->flag == 'p')
		print_p(list, ap);
	return (0);
}
