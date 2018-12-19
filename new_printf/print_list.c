/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 10:16:09 by agesp             #+#    #+#             */
/*   Updated: 2018/12/19 16:47:56 by agesp            ###   ########.fr       */
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

int		print_wp(t_plist *list, int len, char zero, int *size)
{
	int		i;
	int		lim;
	int		flag;

	i = -1;
	flag = list->min_width + list->precision < len ?
		0 : (list->min_width - list->precision);
	lim = list->min_width > list->precision ?
		flag : 0;
	flag = zero == '-' ? 1 : 0;
	i += list->precision >= len ? flag : 0;
	if (lim > 0 && list->min_width - len > 0)
		while (++i < (lim = list->precision > len ? lim: list->min_width - len))
			list->sign == '0' && list->precision == 0 ? ft_putchar('0') : ft_putchar(' ');
	if (zero == '-')
		ft_putchar('-');
	*size = i == -1 ? *size + 0 : *size + i;
	i = -1;
	lim = list->precision + flag - len;
	if (lim > 0)
		while (++i < lim)
			ft_putchar('0');
	*size = i == -1 ? *size +  0 : *size + i;
	if (flag == 1)
		return (1);
	return (0);
}

void	print_width(t_plist *list, int len, int *size)
{
	int		i;

	i = -1;
	if (list->min_width > len)
		while (++i < list->min_width - len)
			ft_putchar(' ');
	*size += i;
}

void	print_int(t_plist *list, va_list *ap, int *size)
{
	char	*ret;
	int	i;

	i = -1;
	ret = convert_dioux(list->flag, ap, 10, list->conversion);

	if (print_wp(list, ft_strlen(ret), ret[0], size))
		ret++;
	if (ft_strcmp(ret, "0") == 0 && list->precision == 0 && list->min_width == 0)
		return ;
	ft_putstr(ret);
	*size += (int)ft_strlen(ret);
}

void	print_o(t_plist *list, va_list *ap, int *size)
{
	char	*ret;
	int	i;

	i = -1;
	ret = convert_dioux(list->flag, ap, 10, list->conversion);
	if (print_wp(list, ft_strlen(ret), ret[0], size))
		ret++;
	if (ft_strcmp(ret, "0") == 0 && list->precision == 0 && list->min_width == 0)
		return ;
	ft_putstr(ret);
	*size += (int)ft_strlen(ret);
}

void	print_x(t_plist *list, va_list *ap, int *size)
{
	char	*ret;
	int	i;

	i = -1;
	ret = NULL;
	ret = convert_dioux(list->flag, ap, 16, list->conversion);
	if (print_wp(list, ft_strlen(ret), ret[0], size))
		ret++;
	if (ft_strcmp(ret, "0") == 0 && list->precision == 0 && list->min_width == 0)
		return ;
	ft_putstr(ret);
	*size += (int)ft_strlen(ret);
}

void	print_u(t_plist *list, va_list *ap, int *size)
{
	char	*ret;
	int	i;

	i = -1;
	ret = convert_dioux(list->flag, ap, 10, list->conversion);
	if (print_wp(list, ft_strlen(ret), ret[0], size))
		ret++;
	if (ft_strcmp(ret, "0") == 0 && list->precision == 0 && list->min_width == 0)
		return ;
	ft_putstr(ret);
	*size += (int)ft_strlen(ret);
}

void	print_c(t_plist *list, va_list *ap, int *size)
{
	print_width(list, 1, size);
	w_print_char(va_arg(*ap, wchar_t));
}

void	print_s(t_plist *list, va_list *ap, int *size)
{
	int		i;
	char	*s;

	i = 0;
	s = va_arg(*ap, char*);
	print_width(list, ft_strlen(s), size); 
	while (s[i])
	{
		w_print_char((unsigned int)s[i]);
		i++;
	}
	*size += (int)ft_strlen(s);
}

int		print_list(t_plist *list, va_list *ap)
{
	int		size;

	size = 0;
	if (list->flag == 'd' || list->flag == 'i')
		print_int(list, ap, &size);
	if (list->flag == 'o')
		print_o(list, ap, &size);
	if (list->flag == 'u')
		print_u(list, ap, &size);
	if (list->flag == 'x' || list->flag == 'X')
		print_x(list, ap, &size);
	if (list->flag == 'c')
	{
		size++;
		print_c(list, ap, &size);
	}
	if (list->flag == 's')
		print_s(list, ap, &size);
	return (size);
}
