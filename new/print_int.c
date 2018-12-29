/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 11:22:04 by agesp             #+#    #+#             */
/*   Updated: 2018/12/29 11:40:10 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_int(char c)
{
	if (c == 'd' || c == 'i' || c == 'f')
		return (1);
	return (0);
}

void	do_nothing(void)
{
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
