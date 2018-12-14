/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 12:01:33 by agesp             #+#    #+#             */
/*   Updated: 2018/12/14 16:14:28 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_with_d(va_list *ap, int is_zero, int digit)
{
	char	*s;
	int		i;

	i = -1;
	s = ft_itoa(va_arg(*ap, int));
	if (digit < ft_strlen(s))
	{
		ft_putstr(s);
		return ;
	}
	if (is_zero == 1)
		while (++i < digit - ft_strlen(s))
			ft_putnbr(0);
	else
		while (++i < digit - ft_strlen(s))
			ft_putchar(' ');
	ft_putstr(s);
}

void	print_width_s(va_list *ap, int digit)
{
	char	*s;
	int		i;
	
	i = -1;
	s = va_arg(*ap, char*);
	if (digit < ft_strlen(s))
	{
		ft_putstr(s);
		return ;
	}
	while (++i < digit - ft_strlen(s))
		ft_putchar(' ');
	ft_putstr(s);
}

int		print_width(va_list *ap, int flag, int is_zero, int digit)
{
	if (flag == 1)
		print_with_d(ap, is_zero, digit);
	if (flag == 2 && is_zero == -1)
		print_width_s(ap, digit);
	if (flag == 5)
		return (2);
	return (1);
}

int		reckon_width(const char *format, int pos, va_list *ap)
{
	int		i;
	int		flag;
	int		digit;
	char	*save;
	int		is_zero;

	digit = 0;
	i = pos;
	is_zero = -1;
	if (format[i] == '0')
	{
		is_zero = 1;
		while (format[i] == '0')
			i++;
	}
	while (ft_isdigit(format[i]))
		i++;
	if (!(save = ft_strnew(i - pos)))
		return (0);
	digit = ft_atoi(ft_strncpy(save, format + pos, i - pos));
	free(save);
	flag = reckon_flag(format, i, ap);
	if (print_width(ap, flag, is_zero, digit) == 2)
		precision_width(format, i + 1, ap, digit);
	return (1);
}
