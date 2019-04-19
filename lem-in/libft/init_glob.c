/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_glob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:42:35 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/05 13:47:43 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/includes/printf.h"

t_parsing				*wildcartcheck(const char **format, t_parsing *lst,\
						va_list arg)
{
	(*format)--;
	lst->attr = 1;
	lst->wild = va_arg(arg, int);
	if (lst->wild < 0)
		lst->wild = 0;
	if (**format == '-')
		lst->min = lst->wild;
	else if (**format == '0')
		lst->prec = lst->wild;
	else if (**format == '.')
		lst->prec = lst->wild;
	else
		lst->decimal = lst->wild;
	(*format) += 2;
	return (lst);
}

static t_parsing		*parsing_attr(t_parsing *lst)
{
	if (lst->min)
		lst->min = lst->decimal;
	else if (lst->zero)
		lst->zero = lst->decimal;
	if (lst->prec)
	{
		if (lst->prec == -2)
		{
			lst->prec = lst->decimal;
			lst->decimal = 0;
		}
		if (lst->prec > 0)
			lst->zero = 0;
	}
	if (lst->min || lst->zero)
		lst->decimal = 0;
	return (lst);
}

void					no_conv(t_parsing *lst, int *ret, char c)
{
	char *str;

	str = ft_strdup("");
	str[0] = c;
	lst->conv = '0';
	if (lst->zero)
		lst->zero = lst->decimal;
	str = controller_attr(lst, str);
	ft_print(str, ret);
	free(str);
}

const char				*glob_init(va_list arg, const char *format,\
						int *ret, t_parsing *lst)
{
	while (*format)
	{
		if (init_attr(&lst, format))
			format++;
		else if (*format == '*')
			lst = wildcartcheck(&format, lst, arg);
		else if (*format == '.')
			lst = init_prec(lst, &format);
		else if (is_digit(*format))
			lst->decimal = ft_atoi_adv(&format);
		else if (initialiser_mod_long(&lst, &format))
			continue ;
		else if (init_conv(&format, &lst))
			break ;
		else
			break ;
	}
	if (!lst->conv)
	{
		no_conv(lst, ret, *format);
		format++;
	}
	lst = parsing_attr(lst);
	parsing_conv(arg, lst, ret);
	return (format);
}
