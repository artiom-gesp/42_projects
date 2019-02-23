/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 11:22:04 by agesp             #+#    #+#             */
/*   Updated: 2019/02/11 13:08:47 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_zero(int lim)
{
	int i;

	i = -1;
	if (lim > 0)
		while (++i < lim)
			ft_putchar('0');
	return (i);
}

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
	if (!zero_ret(&ret, list, &minus))
		return ;
	if (list->precision >= list->min_width)
		print_precision(list, ret, 1);
	else if (list->precision < list->min_width && minus)
		print_pw_minus(list, ret);
	else if (list->precision < list->min_width)
	{
		print_wp(list, (int)ft_strlen(ret), ret)
			? ft_putstr(ret + 1) : ft_putstr(ret);
		list->size += ret[0] != '-' ? (int)ft_strlen(ret)
			: (int)ft_strlen(ret) - 1;
	}
	ft_strcmp(ret, "")
		&& ft_strcmp(ret, "-9223372036854775808") ? free(ret) : do_nothing();
}
