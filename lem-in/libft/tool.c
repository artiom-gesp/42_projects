/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:42:35 by kecosmon          #+#    #+#             */
/*   Updated: 2018/06/01 17:42:37 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/includes/printf.h"

t_parsing	*init_lst(t_parsing *lst)
{
	lst->car = 0;
	lst->decimal = 0;
	lst->attr = 0;
	lst->prec = 0;
	lst->mod_long = 0;
	lst->conv = 0;
	lst->hash = 0;
	lst->min = 0;
	lst->max = 0;
	lst->space = 0;
	lst->wild = 0;
	lst->zero = 0;
	lst->cotes = 0;
	lst->h = 0;
	lst->hh = 0;
	lst->l = 0;
	lst->ll = 0;
	lst->j = 0;
	lst->z = 0;
	return (lst);
}

const char	*ft_print(const char *format, int *ret)
{
	int i;

	i = 0;
	if (format)
		while (*format != '%' && *format)
		{
			ft_putchar(*format++);
			i++;
		}
	*ret += i;
	return (format);
}

void		strprint(char *format, int *ret)
{
	int i;

	i = 0;
	while (format[i])
		ft_putchar(format[i++]);
	*ret += i;
}

int			putlstwstr(t_parsing *lst, wchar_t *wstr)
{
	int	len;

	len = ft_wstrlen(wstr);
	ft_putwstr(wstr);
	freewstr(wstr);
	if (len == 0 && lst->conv == 'C')
	{
		ft_putwchar(0);
		return (1);
	}
	return (len);
}

int			is_special_prec(t_parsing *lst, char *str)
{
	return (((issigned(lst) || isunsigned(lst) || lst->conv == 'p')
		&& lst->prec > 0) || (lst->conv == 'p' &&\
		lst->prec && ft_strcmp(str, "0")) ||\
		(lst->conv == 'c' && lst->zero) || (lst->conv == 's' && lst->zero)
		|| (lst->conv == '%' && lst->zero) || (lst->conv == '0' && lst->zero));
}
