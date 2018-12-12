/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 16:35:06 by agesp             #+#    #+#             */
/*   Updated: 2018/12/12 17:28:04 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	do_print(va_list *ap, int flag)
{
	if (flag == 1)
		ft_putnbr(va_arg(*ap, int));
	if (flag == 2)
		ft_putstr(va_arg(*ap, char*));
	if (flag == 3)
		ft_putchar(va_arg(*ap, int));
}

int		reckon_flag(const char *format, int pos, va_list *ap)
{
	int flag;

	flag = -1;
	if (format[pos] == 'd')
		flag = 1;
	if (format[pos] == 's')
		flag = 2;
	if (format[pos] == 'c')
		flag = 3;
	if (format[pos] == '.')
	{
	   flag = reckon_dot(format, pos + 1, ap);
	   return (-1);
	}
	return (flag);
}
