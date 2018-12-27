/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 13:02:13 by agesp             #+#    #+#             */
/*   Updated: 2018/12/21 17:52:52 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_int(char c)
{
	if (c == 'd' || c == 'i')
		return (1);
	return (0);
}

void	do_nothing()
{
}

void	print_hash(t_plist *list, char *ret)
{
	if ((list->flag == 'x' || list->flag == 'X')
			&& ft_strchr(list->sign, '#')
			&& ft_strcmp(ret, "0"))
	{
		ft_putchar('0');
		ft_putchar(list->flag);
		list->size += 2;
	}
	if (list->flag == 'o' && ft_strchr(list->sign, '#')
			&& ft_strcmp(ret, "0"))
	{
		if (list->precision <= (int)ft_strlen(ret))
		{
			ft_putchar('0');
			list->size++;
		}
		else if (list->min_width > list->precision)
			list->min_width++;
	}
}

void	is_minus(char **ret, int *len, t_plist *list)
{
	char	*save;
	int		yolo;

	ft_putchar('-');
	save = *ret;
	yolo = *len;
	if (list->precision >= yolo || (list->precision >= list->min_width && *len > list->precision))
		list->size++;
	save++;
	yolo--;
	*ret = save;
	*len = yolo;
	if (list->precision >= list->min_width)
		list->min_width--;
}

void	print_precision_sign(t_plist *list, char *ret, int flag)
{
	if (ret[0] != '-' && flag && ft_strchr(list->sign, '+'))
	{
		ft_putchar('+');
		list->size++;
	}
	if (ret[0] != '-' && flag && ft_strchr(list->sign, ' '))
	{
		ft_putchar(' ');
		list->size++;
	}
}

void	print_precision(t_plist *list, char *ret, int flag)
{
	int	i;
	int	len;

	i = 0;

	len = (int)ft_strlen(ret);
	print_hash(list, ret);
	print_precision_sign(list, ret, is_int(list->flag));
	if (ret[0] == '-')
		is_minus(&ret, &len, list);
	if (list->precision - len > 0)
		while (i < list->precision - len)
		{
			ft_putchar('0');
			i++;
			list->size++;
		}
	ft_putstr(ret);
	if (flag || list->precision > len)
		list->size += len;
}

void	print_minus_wd(t_plist *list, char *ret, int plus, int len)
{
	int	i;
	int	lim;

	i = -1;
	lim = list->min_width + list->precision < len ? 0 :
		list->min_width - list->precision;
	if (plus && list->min_width > len && is_int(list->flag))
	{
		if (list->precision > len && list->precision > list->min_width)
		{
			ft_putchar(plus);
			ft_putstr(ret);
		}
		lim--;
		while (++i < (lim = list->precision > len ? lim: list->min_width - len - 1))
			ft_putchar(' ');
	}
	else if ((!plus || !is_int(list->flag))  && (list->min_width - len) > 0)
	{
		if (list->precision > len && list->precision > list->min_width)
			ft_putstr(ret);
		while (++i < (lim = list->precision > len ? lim : list->min_width - len))
			ft_putchar(' ');
	}
	else if (list->precision > len)
		ft_putstr(ret);
	list->size += list->precision > len ? i : len + i;
}

void	print_pw_minus(t_plist *list, char *ret)
{
	int	plus;
	int 	len;

	len = (int)ft_strlen(ret);
	plus = 0;
	plus = ft_strchr(list->sign, ' ') && ret[0] != '-' && is_int(list->flag) ? ' ' : 0;
	plus = ft_strchr(list->sign, '+') && ret[0] != '-' && is_int(list->flag) ? '+' : plus;
	if (list->precision <= len && list->min_width <= len)
	{
		plus ? ft_putchar(plus) : do_nothing();
		print_hash(list, ret);
		ft_putstr(ret);
		plus = plus ? 1 : 0;
		list->size += (len + plus);
	}
	else if (list->min_width > len)
	{
		print_precision(list, ret, 0);
		print_minus_wd(list, ret, plus, len);
	}
}

void	integer_print(t_plist *list, va_list *ap)
{
	char	*ret;
	int		minus;

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










