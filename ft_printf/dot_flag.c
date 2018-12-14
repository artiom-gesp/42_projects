/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 16:27:43 by agesp             #+#    #+#             */
/*   Updated: 2018/12/14 17:39:04 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	do_print_dot(va_list *ap, int flag, int digit)
{
	char		*line;
	int			d;
	int			pos;
	long long	u;

	pos = -1;
	line = NULL;
	d = 0;
	if (flag == 2)
	{
		line = va_arg(*ap, char*);
		while (line[++pos] && pos < digit)
			ft_putchar(line[pos]);
	}
	if (flag == 1 && ((ft_strcmp(line = ft_itoa(va_arg(*ap, int)), "0") != 0)
				|| digit != 0))
	{
		if (ft_strlen(line) < digit)
			while (++pos < digit - ft_strlen(line))
				ft_putchar('0');
		ft_putstr(line);
	}
	if (flag == 7)
	{
		u = va_arg(*ap, long long);
			if (u < 0)
				u *= -1;
		if (ft_strcmp(line = ft_itoa_base(va_arg(*ap, long long), 10), "0") != 0
				|| digit != 0)
		{
			if (ft_strlen(line) < digit)
				while (++pos < digit - ft_strlen(line))
					ft_putchar('0');
			ft_put_long_nbr(u);
		}
	}
}

int		reckon_dot(const char *format, int pos, va_list *ap)
{
	int		i;
	int		flag;
	int		digit;
	char	*save;

	digit = 0;
	i = pos;
	save = NULL;
	while (ft_isdigit(format[i]))
		i++;
	if (!(save = ft_strnew(i - pos)))
		return (0);
	digit = ft_atoi(ft_strncpy(save, format + pos, i - pos));
	free(save);
	flag = reckon_flag(format, i, ap);
	do_print_dot(ap, flag, digit);
	return (1);
}
