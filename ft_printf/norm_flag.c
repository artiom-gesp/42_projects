/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 16:35:06 by agesp             #+#    #+#             */
/*   Updated: 2018/12/14 17:28:03 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	do_print(va_list *ap, int flag, int pos, const char *format)
{
	if (flag == 1)
		ft_putnbr(va_arg(*ap, int));
	if (flag == 2)
		ft_putstr(va_arg(*ap, char*));
	if (flag == 3)
		ft_putchar(va_arg(*ap, int));
	if (flag == 4)
		ft_putchar('%');
	if (flag == 5)
		reckon_dot(format, pos + 1, ap);
	if (flag == 6)
		reckon_width(format, pos, ap);
	if (flag == 7)
		print_u_flag(ap);
}

int		is_dot_val(const char *format, int pos)
{
	if (format[pos] == 'd' || format[pos] == 's'
			|| format[pos] == 'i' || format[pos] == 'u')
		return (1);
	return (0);
}

int		is_flag_val(const char *format, int pos)
{
	if (format[pos] == 'd' || format[pos] == 's' || format[pos] == 'c'
				|| format[pos] == 'i' || format[pos] == 'u')
		return (1);
	if (format[pos] == '.' && ft_isdigit(format[pos + 1]))
	{
		pos++;
		while (ft_isdigit(format[pos]))
			pos++;
		return (is_dot_val(format, pos));
	}
	if (ft_isdigit(format[pos++]))
	{
			while (ft_isdigit(format[pos]))
				pos++;
			return (is_flag_val(format, pos));
	}
	return (0);
}

int		reckon_flag(const char *format, int pos, va_list *ap)
{
	int flag;

	flag = -1;
	if (!(is_flag_val(format, pos)))
		return (-2);
	if (format[pos] == 'd' || format[pos] == 'i')
 		flag = 1;
	if (format[pos] == 's')
		flag = 2;
	if (format[pos] == 'c')
		flag = 3;
	if (format[pos] == '%')
		flag = 4;
	if (format[pos] == '.')
		flag = 5;
	if (ft_isdigit(format[pos]))
		flag = 6;
	if (format[pos] == 'u')
		flag = 7;
	return (flag);
}
