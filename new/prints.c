/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 17:01:36 by agesp             #+#    #+#             */
/*   Updated: 2018/12/29 11:51:46 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_c(t_plist *list, va_list *ap)
{
	if (ft_strchr(list->sign, '-'))
	{
		w_print_char(va_arg(*ap, wchar_t));
		print_width(list, 1);
	}
	else
	{
		print_width(list, 1);
		w_print_char(va_arg(*ap, wchar_t));
	}
	list->size++;
}

void	do_print_s(char *s, t_plist *list)
{
	int	i;

	i = -1;
	if (ft_strcmp(s, "") || list->min_width > 1)
	{
		if (!ft_strchr(list->sign, '-'))
			print_width(list, ft_strlen(s));
		while (s[++i])
			w_print_char((unsigned int)s[i]);
		if (ft_strchr(list->sign, '-'))
			print_width(list, (int)ft_strlen(s));
	}
	list->size += i != -1 ? i : 0;
}

void	print_s(t_plist *list, va_list *ap)
{
	int		i;
	char	*s;
	char	*save;

	i = -1;
	save = va_arg(*ap, char*);
	if (!save)
		save = "(null)";
	if (list->precision == 0)
		list->precision = (int)ft_strlen(save);
	if (list->precision == -1)
	{
		list->min_width += list->min_width > 0 ? 1 : 0;
		print_width(list, 1);
		return ;
	}
	if (!(s = ft_strnew(list->precision)))
		return ;
	ft_strncpy(s, save, list->precision);
	do_print_s(s, list);
}

void	print_percent(t_plist *list)
{
	int i;

	i = -1;
	if (ft_strchr(list->sign, '-'))
	{
		ft_putchar('%');
		print_width(list, 1);
	}
	else
	{
		print_width(list, 1);
		ft_putchar('%');
	}
	list->size++;
}

void	print_p(t_plist *list, va_list *ap)
{
	long long	save;
	char		*ret;
	int			len;

	save = (long)va_arg(*ap, void*);
	ret = ft_itoa_base(save, 16, 'a');
	len = (int)ft_strlen(ret);
	len += 2;
	if (ft_strchr(list->sign, '-'))
	{
		ft_putstr("0x");
		ft_putstr(ret);
		print_width(list, len);
	}
	else
	{
		print_width(list, len);
		ft_putstr("0x");
		ft_putstr(ret);
	}
	list->size += len;
}
