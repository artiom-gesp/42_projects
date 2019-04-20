/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 10:16:09 by agesp             #+#    #+#             */
/*   Updated: 2019/01/07 09:53:58 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*convert_md(char flag, va_list *ap, int base)
{
	char	*ret;

	if (flag == 'd' || flag == 'i')
		ret = ft_itoa_base(va_arg(*ap, int), base, flag - 23);
	else if (flag == 'u')
		ret = ft_itoa_base((unsigned int)va_arg(*ap, long long),
				base, flag - 23);
	else
		ret = ft_itoa_base(va_arg(*ap, unsigned int), base, flag - 23);
	return (ret);
}

char	*convert_dioux(char flag, va_list *ap, int base, int conv)
{
	char *ret;

	if (conv == 2 && (flag == 'u' || flag == 'o' || flag == 'x'
				|| flag == 'X'))
		ret = get_u((unsigned long long)va_arg(*ap, long long), base,
				flag - 23);
	else if (conv == 2)
		ret = ft_itoa_base(va_arg(*ap, long long), base, flag - 23);
	else if (conv == 1 && (flag == 'u' || flag == 'x' || flag == 'X'
			|| flag == 'o'))
		ret = get_u((unsigned long)va_arg(*ap, uintmax_t), base, flag - 23);
	else if (conv == 1)
		ret = ft_itoa_base(va_arg(*ap, long), base, flag - 23);
	else if (conv == 3 && (flag == 'd' || flag == 'i'))
		ret = ft_itoa_base((short int)va_arg(*ap, int), base, flag - 23);
	else if (conv == 3)
		ret = ft_itoa_base((unsigned short int)va_arg(*ap, int),
				base, flag - 23);
	else if (conv == 4 && (flag == 'd' || flag == 'i'))
		ret = ft_itoa_base((char)va_arg(*ap, int), base, flag - 23);
	else if (conv == 4)
		ret = ft_itoa_base((unsigned char)va_arg(*ap, int), base, flag - 23);
	else
		ret = convert_md(flag, ap, base);
	return (ret);
}

int		add_start(t_plist *list)
{
	if (ft_strchr(list->sign, '+') || ft_strchr(list->sign, ' '))
		return (1);
	return (0);
}

void	print_sign(t_plist *list, char *ret, int flag)
{
	int	len;

	len = (int)ft_strlen(ret);
	if (list->flag == 'd' || list->flag == 'i' || list->flag == 'f')
	{
		if ((!flag && ft_strchr(list->sign, '0'))
				|| (flag && !ft_strchr(list->sign, '0')))
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
			ft_strchr(list->sign, ' ') ? ft_putchar(' ') : do_nothing();
			list->size += ft_strchr(list->sign, ' ') ? 1 : 0;
		}
		if (!flag && add_start(list) && ret[0] != '-')
			list->min_width--;
	}
}

int		print_list(t_plist *list, va_list *ap)
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
	if (list->flag == 'f')
		print_float(ap, list);
	return (0);
}
