/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prec_width_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:12:07 by agesp             #+#    #+#             */
/*   Updated: 2018/12/14 16:20:51 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_prec_width(va_list *ap, int flag, int precision, int digit)
{
	int		i;
	int		save;

	if (flag == 1)
	{
		if (precision > digit)
			do_print_dot(ap, flag, precision);
		else
		{
			save = precision;
			if (precision == 1 || precision == 0)
				precision = 2;
			while (precision < digit)
			{
				ft_putchar(' ');
				precision++;
			}
			do_print_dot(ap, flag, save);
		}
	}	
}

int		precision_width(const char *format, int pos, va_list *ap, int digit)
{
	int		i;
	char	*save;
	int		precision;
	int 	flag;

	i = pos;
	while (ft_isdigit(format[i] == 0))
		i++;
	while (ft_isdigit(format[i]))
		i++;
	if (!(save = ft_strnew(i - pos)))
		return (0);
	precision = ft_atoi(ft_strncpy(save, format + pos, i - pos));
	free(save);
	flag = reckon_flag(format, i, ap);
	print_prec_width(ap, flag, precision, digit);
	return (1);
}
