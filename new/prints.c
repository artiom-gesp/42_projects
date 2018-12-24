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
	hash = ft_strchr(list->sign, '#') && ft_strcmp(ret, "0") ? 1 : 0;
	if (hash && ft_strcmp(ret, "0") && minus)
		list->min_width -= 1;
	if (!ft_strcmp(ret, "0") && list->precision == -1)
	{
		ret = "";
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
		ret = "";
		hash = 0;
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
	int	i;

	i = -1;
	ret = convert_dioux(list->flag, ap, 10, list->conversion);
	if (print_wp(list, ft_strlen(ret), ret[0]))
		ret++;
	if (ft_strcmp(ret, "0") == 0 && list->precision == 0 && list->min_width == 0)
		return ;
	if (!ft_strchr(list->sign, '-'))
		ft_putstr(ret);
	list->size += (int)ft_strlen(ret);
}

void	print_c(t_plist *list, va_list *ap)
{
	print_width(list, 1);
	w_print_char(va_arg(*ap, wchar_t));
}

void	print_s(t_plist *list, va_list *ap)
{
	int		i;
	char	*s;

	i = 0;
	s = va_arg(*ap, char*);
	if (!s)
	{
		ft_putstr("(null)");
		list->size += 6;
		return ;
	}
	if (ft_strcmp(s, "") || list->min_width > 1)
	{
		if (!ft_strchr(list->sign, '-'))
			list->precision > (int)ft_strlen(s) ?
			print_width(list, ft_strlen(s)) : 
			print_width(list, list->precision != -1 ? list->precision : ft_strlen(s));
		while (list->precision != -1 && list->precision < (int)ft_strlen(s) ? 
				i < list->precision : (s[i]))
		{
			w_print_char((unsigned int)s[i]);
			i++;
		}
		if (ft_strchr(list->sign, '-'))
			list->precision > (int)ft_strlen(s) && list->precision != -1 
				&& ft_strchr(list->sign, '-') ? print_width(list, ft_strlen(s)) : 
				print_width(list, list->precision != -1 ? list->precision : ft_strlen(s));
	}
	list->size += i;
}

void	print_percent(t_plist *list)
{
	int i;

	i = -1;
	if (list->min_width > 1)
	while (++i < list->min_width -1)
	{
		list->size++;
		ft_putchar(' ');
	}
	list->size++;
	ft_putchar('%');
}
