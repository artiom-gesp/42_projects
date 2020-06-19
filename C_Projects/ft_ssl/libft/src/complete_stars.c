/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_stars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 14:45:17 by agesp             #+#    #+#             */
/*   Updated: 2019/01/08 15:45:30 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	complete_start_sign(const char *format, int *pos)
{
	int i;

	i = *pos;
	while (!is_sign(format, i) && !ft_isdigit(format[i])
			&& format[i] != '.' && !correct_flags(format, i)
			&& format[i] == '*')
		i++;
	*pos = i;
}

void	if_flag(int flag, long long precision, int width, t_plist *list)
{
	if (flag == 1)
	{
		list->min_width = width != -1 ? width : list->min_width;
		list->min_width = width == 0 ? -1 : list->min_width;
	}
	if (flag == 2)
	{
		list->precision = precision != -1 ? precision : list->precision;
		list->precision = precision == 0 ? -1 : list->precision;
		list->precision = list->precision < -1 && list->flag == 's'
			? 0 : list->precision;
	}
}

void	complete_stars_w(va_list *ap, const char *format,
		int pos, t_plist *list)
{
	int	i;
	int	width;
	int	flag;

	i = 0;
	flag = 0;
	width = -1;
	while (i < pos && format[i] != '%')
		i++;
	while (i < pos && format[i] != '.')
	{
		width = format[i] == '*' && width == -1 ? va_arg(*ap, int) : -1;
		if (format[i] == '*')
			flag = 1;
		if (width < 0 && width != -1)
		{
			width *= -1;
			list->sign[3] = '-';
		}
		i++;
	}
	if_flag(flag, 0, width, list);
}

void	complete_stars_p(va_list *ap, const char *format,
		int pos, t_plist *list)
{
	int			i;
	long long	precision;
	int			flag;
	long long	save;

	i = 0;
	flag = 0;
	precision = -1;
	save = 0;
	while (i < pos && format[i] != '.')
		i++;
	if (format[i] == '.')
	{
		while (i < pos)
		{
			if (format[i] == '*')
				flag = 2;
			save = format[i] == '*' && precision == -1
				? va_arg(*ap, int) : 0;
			save = save < 0 && list->flag != 's' ? list->min_width : save;
			precision = format[i++] == '*' && precision == -1
				? save : -1;
		}
	}
	if_flag(flag, precision, 0, list);
}

void	complete_stars(va_list *ap, const char *format, int pos, t_plist *list)
{
	complete_stars_w(ap, format, pos, list);
	complete_stars_p(ap, format, pos, list);
}
