/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 10:16:09 by agesp             #+#    #+#             */
/*   Updated: 2018/12/20 16:56:41 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*convert_dioux(char flag, va_list *ap, int base, int conv)
{
	char *ret;

	ret = NULL;
	if (conv == 2)
		ret = ft_itoa_base(va_arg(*ap, long long), base, flag - 23);
	else if (conv == 1)
		ret = ft_itoa_base(va_arg(*ap, long), base, flag - 23);
	else if (conv == 3 && (flag == 'd' || flag == 'i'))
		ret = ft_itoa_base((short int)va_arg(*ap, int), base, flag - 23);
	else if (conv == 3)
		ret = ft_itoa_base((unsigned short int)va_arg(*ap, int), base, flag - 23);
	else if (conv == 4 && (flag == 'd' || flag == 'i'))
		ret = ft_itoa_base((char)va_arg(*ap, int), base, flag - 23);
	else if (conv == 4)
		ret = ft_itoa_base((unsigned char)va_arg(*ap, int), base, flag - 23);
	else if (flag == 'd' || flag == 'i')
		ret = ft_itoa_base(va_arg(*ap, int), base, flag - 23);
	else if (flag == 'o' || flag == 'u' || flag == 'x' || flag == 'X')
		ret = ft_itoa_base(va_arg(*ap, unsigned int), base, flag - 23);
	return (ret);
}

int		print_wp(t_plist *list, int len, char zero, int ou)
{
	int		i;
	int		lim;
	int		flag;

	i = -1;
	if (ft_strchr(list->sign, '#') && zero != '~' && ft_strchr(list->sign, '0') && ou)
	{
		if (list->flag == 'X' || list->flag == 'x')
		{
			ft_putchar('0');
			ft_putchar(list->flag);
		}
	}
	flag = list->min_width + list->precision < len ?
		0 : (list->min_width - list->precision);
	lim = list->min_width > list->precision ?
		flag : 0;
	flag = zero == '-' ? 1 : 0;
	i += list->precision >= len ? flag : 0;
	if (lim > 0 && list->min_width - len > 0)
		while (++i < (lim = list->precision > len ? lim: list->min_width - len))
			ft_strchr(list->sign, '0') && list->precision == 0 ? ft_putchar('0') : ft_putchar(' ');
	if (zero == '-' && !ou)
	{
		list->size++;
		ft_putchar('-');
	}
	if (!ft_strchr(list->sign, '0') && ft_strchr(list->sign, '#') && ou)
	{
		if (list->flag == 'X' || list->flag == 'x')
		{
			ft_putchar('0');
			ft_putchar(list->flag);
		}
	}
	list->size = i == -1 ? list->size + 0 : list->size + i;
	i = -1;
	lim = list->precision + flag - len;
	if (lim > 0)
		while (++i < lim)
			ft_putchar('0');
	list->size = i == -1 ? list->size +  0 : list->size + i;
	if (flag == 1)
		return (1);
	return (0);
}

void	print_width(t_plist *list, int len)
{
	int		i;

	i = -1;
	if (list->min_width > len)
		while (++i < list->min_width - len)
			ft_putchar(' ');
	list->size = i == -1 ? list->size + 0 : list->size + i;
}

void	print_int(t_plist *list, va_list *ap)
{
	char	*ret;
	int	i;
	int ou;

	ou = 0;
	i = -1;
	ret = convert_dioux(list->flag, ap, 10, list->conversion);
	if (ft_strcmp(ret, "0") == 0)
	{
			if (list->precision == 0 && list->min_width == 0)
				return ;
			else
				ret[0] = '~';
	}
	if (ft_strchr(list->sign, '-'))
	{
		if (ret[0] == '-')
		{
			list->size++;
			ou = 1;
		}
		ret[0] != '~' ? ft_putstr(ret) : ft_putchar('0');
	}
	if (print_wp(list, ft_strlen(ret), ret[0], ou))
		ret++;
	if (!ft_strchr(list->sign, '-'))
		ret[0] != '~' ? ft_putstr(ret) : ft_putchar('0');
	list->size += (int)ft_strlen(ret);
}

void	print_o(t_plist *list, va_list *ap)
{
	char	*ret;
	int	i;

	i = -1;
	ret = convert_dioux(list->flag, ap, 8, list->conversion);
	if (print_wp(list, ft_strlen(ret), ret[0], 0))
		ret++;
	if (ft_strcmp(ret, "0") == 0 && list->precision == 0 && list->min_width == 0)
		return ;
	ft_putstr(ret);
	list->size += (int)ft_strlen(ret);
}

void	print_x(t_plist *list, va_list *ap)
{
	char	*ret;
	int		i;
	int		hash;
	int		ou;

	i = -1;
	ret = NULL;
	hash = 0;
	ou = 1;
	ret = convert_dioux(list->flag, ap, 16, list->conversion);
	if (ft_strchr(list->sign, '#') && ft_strcmp(ret, "0"))
		hash = 2;
	if (ft_strcmp(ret, "0") == 0)
	{
			if (list->precision == 0 && list->min_width == 0)
				return ;
			else
				ret[0] = '~';
	}
	if (ft_strchr(list->sign, '-'))
	{
		if (ft_strchr(list->sign, '#') && ft_strcmp(ret, "0"))
		{
			ft_putchar('0');
			ft_putchar(list->flag);
			ou = 0;
		}
		ret[0] != '~' ? ft_putstr(ret) : ft_putchar('0');
	}
	if (print_wp(list, ft_strlen(ret) + hash, ret[0], ou))
		ret++;
	if (!ft_strchr(list->sign, '-'))
		ret[0] != '~' ? ft_putstr(ret) : ft_putchar('0');
	list->size += ((int)ft_strlen(ret) + hash);
}

void	print_u(t_plist *list, va_list *ap)
{
	char	*ret;
	int	i;

	i = -1;
	ret = convert_dioux(list->flag, ap, 10, list->conversion);
	if (print_wp(list, ft_strlen(ret), ret[0], 0))
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
		print_width(list, ft_strlen(s));
		while (s[i])
		{
			w_print_char((unsigned int)s[i]);
			i++;
		}
	}
	list->size += (int)ft_strlen(s);
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

int	print_list(t_plist *list, va_list *ap)
{
	if (list->flag == 'd' || list->flag == 'i')
		print_int(list, ap);
	if (list->flag == 'o')
		print_o(list, ap);
	if (list->flag == 'u')
		print_u(list, ap);
	if (list->flag == 'x' || list->flag == 'X')
		print_x(list, ap);
	if (list->flag == 'c')
	{
		list->size++;
		print_c(list, ap);
	}
	if (list->flag == 's')
		print_s(list, ap);
	if (list->flag == '%')
		print_percent(list);
	return (0);
}
