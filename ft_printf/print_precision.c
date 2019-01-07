/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 11:24:44 by agesp             #+#    #+#             */
/*   Updated: 2019/01/07 11:47:04 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_hash(t_plist *list, char *ret)
{
	if (((list->flag == 'x' || list->flag == 'X')
			&& ft_strchr(list->sign, '#')
			&& ft_strcmp(ret, "0")) || list->flag == 'p')
	{
		ft_putchar('0');
		ft_putchar(list->flag != 'p' ? list->flag : 'x');
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
	if (list->precision >= yolo || (list->precision >= list->min_width
				&& *len > list->precision))
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
