/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 17:01:36 by agesp             #+#    #+#             */
/*   Updated: 2018/12/21 17:06:54 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_o(t_plist *list, va_list *ap)
{
	char	*ret;
	int	hash;
	int	minus;

	minus = ft_strchr(list->sign, '-') ? 1 : 0;
	ret = convert_dioux(list->flag, ap, 8, list->conversion);
	hash = ft_strchr(list->sign, '#') ? 1 : 0;
	if (hash && ft_strcmp(ret, "0") && minus)
		list->min_width -= 1;
	if (!ft_strcmp(ret, "0") && list->precision == -1)
	{
		if (!hash && list->min_width == 0)
			return ;
		ret = hash ? "0" : "";
		hash = 0;
	}
	if (list->precision >= list->min_width)
		print_precision(list, ret, 1);
	else if (list->precision < list->min_width && minus)
		print_pw_minus(list, ret);
	else if (list->precision < list->min_width)
	{
		list->min_width -= hash == 1 ? 1 : 0;
		print_wp_x(list, ft_strlen(ret), hash);
		ft_putstr(ret);
		list->size += (int)ft_strlen(ret);
	}
}

void	print_x(t_plist *list, va_list *ap)
{
	int		minus;
	char		*ret;
	int		hash;

	minus = ft_strchr(list->sign, '-') ? 1 : 0;
	ret = convert_dioux(list->flag, ap, 16, list->conversion);
	hash = ft_strchr(list->sign, '#') && ft_strcmp(ret, "0") ? 1 : 0;
	if (hash && ft_strcmp(ret, "0") && minus)
		list->min_width -= 2;
	if (!ft_strcmp(ret, "0") && list->precision == -1)
	{
		if (list->min_width == 0)
			return ;
		else
			ret = "";
	}
	if (list->precision >= list->min_width)
		print_precision(list, ret, 1);
	else if (list->precision < list->min_width && minus)
		print_pw_minus(list, ret);
	else if (list->precision < list->min_width)
	{
		list->min_width -= hash == 1 ? 2 : 0;
		print_wp_x(list, ft_strlen(ret), hash);
		ft_putstr(ret);
		list->size += (int)ft_strlen(ret);
	}
}

void	print_u(t_plist *list, va_list *ap)
{
	char	*ret;
	int	minus;

	minus = ft_strchr(list->sign, '-') ? 1 : 0;
	ret = convert_dioux(list->flag, ap, 10, list->conversion);
	if (!ft_strcmp(ret, "0") && list->precision == -1)
	{
		if (list->min_width == 0)
			return ;
		ret = "";
	}
	if (list->precision >= list->min_width)
		print_precision(list, ret, 1);
	else if (list->precision < list->min_width && minus)
		print_pw_minus(list, ret);
	else if (list->precision < list->min_width)
	{
		if (print_wp(list, (int)ft_strlen(ret), ret))
		{
			ret++;
		}
		ft_putstr(ret);
		list->size += (int)ft_strlen(ret);
	}
}

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

void	print_s(t_plist *list, va_list *ap)
{
	int		i;
	char	*s;
	char	*save;

	i = -1;
	save = va_arg(*ap, char*);
	if (!save)
	{
		save = "(null)";
	}
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
	int		len;

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
