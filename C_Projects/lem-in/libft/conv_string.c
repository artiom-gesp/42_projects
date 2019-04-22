/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:42:35 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/05 13:29:18 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/includes/printf.h"

void			spec_pars_string(t_parsing *lst, int *ret, int co, char *str)
{
	str = controller_attr(lst, str);
	strprint(str, ret);
	if (co == 1)
	{
		write(1, &lst->car, 1);
		*ret += 1;
	}
	freestr(str);
}

void			conv_string(va_list arg, t_parsing *lst, int *ret)
{
	char	*str;
	int		co;

	co = 0;
	str = NULL;
	if (lst->conv == '%')
		str = ft_strdup("%");
	else if (lst->conv == 'c')
	{
		lst->car = va_arg(arg, int);
		if (lst->car == 0)
			co = 1;
		str = ft_strnew(1);
		str[0] = lst->car;
	}
	else
	{
		str = va_arg(arg, char *);
		if (!str && !lst->zero)
			str = ft_strdup("(null)");
		else
			str = ft_strdup(str);
	}
	spec_pars_string(lst, ret, co, str);
}

void			conv_wstr(va_list arg, t_parsing *lst, int *ret)
{
	wchar_t	*wstr;

	if (lst->conv == 'C')
	{
		wstr = (wchar_t*)malloc(sizeof(wchar_t) * 2);
		wstr[0] = va_arg(arg, int);
		wstr[1] = '\0';
	}
	else
	{
		wstr = va_arg(arg, wchar_t *);
		if (!wstr)
			wstr = ft_wcsdup(L"(null)");
		else
			wstr = ft_wcsdup(wstr);
		wstr = applyprecisionwchar(lst, wstr);
	}
	wstr = applywidthwchar(lst, wstr);
	*ret += putlstwstr(lst, wstr);
}
