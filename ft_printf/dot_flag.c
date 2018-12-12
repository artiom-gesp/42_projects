/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 16:27:43 by agesp             #+#    #+#             */
/*   Updated: 2018/12/12 17:27:33 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	do_print_dot(va_list *ap, int flag, int digit)
{
	char	*line;
	int		pos;

	pos = -1;
	line = va_arg(*ap, char*);
	if (flag == 2)
		while (++pos < digit)
			ft_putchar(line[pos]);		
}

int		reckon_dot(const char *format, int pos, va_list *ap)
{
	int		i;
	int		flag;
	int		digit;
	char	*save;

	digit = 0;
	i = pos;
	while (ft_isdigit(format[i]))
		i++;
	save = malloc(sizeof(char) * (i - pos));
	digit = ft_atoi(ft_strncpy(save, format + pos, i - pos));
	free(save);
	flag = reckon_flag(format, i, ap);
	do_print_dot(ap, flag, digit);
	return (1);
}
