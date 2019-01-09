/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 12:15:22 by agesp             #+#    #+#             */
/*   Updated: 2019/01/08 15:47:52 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		are_flags_correct(const char *format)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (format[i + 1])
	{
		if (format[i] == '%')
		{
			i++;
			if (!(flag = correct_flags(format, i)))
				return (0);
			i = flag;
		}
		else
			i++;
	}
	return (1);
}

void	reset_list(t_plist *list)
{
	int	i;

	i = -1;
	list->flag = 0;
	list->conversion = 0;
	list->precision = 0;
	list->min_width = 0;
	while (++i < 4)
		list->sign[i] = 'z';
	list->size = 0;
}

int		make_plist(const char *format, va_list *ap)
{
	int			i;
	t_plist		*list;
	int			ret;

	i = 0;
	ret = 0;
	list = malloc(sizeof(t_plist));
	while (i < (int)ft_strlen(format))
	{
		reset_list(list);
		if (format[i] == '%')
		{
			i++;
			complete_list(format, &i, list, ap);
			print_list(list, ap);
			ret += list->size;
		}
		if (format[i] != '%' && i < (int)ft_strlen(format))
		{
			ft_putchar(format[i++]);
			ret++;
		}
	}
	free(list);
	return (ret);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;

	i = 0;
	va_start(ap, format);
	if (!(are_flags_correct(format)))
		return (0);
	i = make_plist(format, &ap);
	return (i);
}
