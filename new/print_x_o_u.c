/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x_o_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 11:44:22 by agesp             #+#    #+#             */
/*   Updated: 2019/01/07 10:31:44 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		zero_ret(char **ret, t_plist *list, int *hash)
{
	if (list->flag == 'o')
	{
		if (!ft_strcmp(*ret, "0") && list->precision == -1)
		{
			free(*ret);
			if (!(*hash) && list->min_width == 0)
				return (0);
			*ret = *hash ? "0" : "";
			*hash = 0;
		}
	}
	else
	{
		if (!ft_strcmp(*ret, "0") && list->precision == -1)
		{
			free(*ret);
			if (list->min_width == 0)
				return (0);
			else
				*ret = "";
		}
	}
	return (1);
}

void	print_u(t_plist *list, va_list *ap)
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
		if (print_wp(list, (int)ft_strlen(ret), ret))
		{
			ret++;
		}
		ft_putstr(ret);
		list->size += (int)ft_strlen(ret);
	}
	ft_strcmp(ret, "") ? free(ret) : do_nothing();
}

void	print_o(t_plist *list, va_list *ap)
{
	char	*ret;
	int		hash;
	int		minus;

	minus = ft_strchr(list->sign, '-') ? 1 : 0;
	ret = convert_dioux(list->flag, ap, 8, list->conversion);
	hash = ft_strchr(list->sign, '#') ? 1 : 0;
	if (!zero_ret(&ret, list, &hash))
		return ;
	if (hash && ft_strcmp(ret, "0") && minus)
		list->min_width -= 1;
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
	ft_strcmp(ret, "") && ft_strcmp(ret, "0") ? free(ret) : do_nothing();
}

void	print_x(t_plist *list, va_list *ap)
{
	int		minus;
	char	*ret;
	int		hash;

	minus = ft_strchr(list->sign, '-') ? 1 : 0;
	ret = convert_dioux(list->flag, ap, 16, list->conversion);
	hash = ft_strchr(list->sign, '#') && ft_strcmp(ret, "0") ? 1 : 0;
	if (!zero_ret(&ret, list, &hash))
		return ;
	if (hash && ft_strcmp(ret, "0") && minus)
		list->min_width -= 2;
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
	ft_strcmp(ret, "") ? free(ret) : do_nothing();
}
