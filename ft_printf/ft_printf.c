/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 13:43:22 by agesp             #+#    #+#             */
/*   Updated: 2018/12/14 17:41:26 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_first_arg(const char * format)
{
	int i;

	i = 0;
	while (format[i] && format[i] != '%')
	{
		i++;
	}
	return (i);
}

int		print_inter(const char *format, int pos)
{
	int i;
	char	*line;

	i = get_first_arg(format);
	line = ft_strnew(i);
	line = ft_strncpy(line, format, i);
	ft_putstr(line);
	free(line);
	return (i + pos);
}

int		get_end_flag(const char *format, int pos, va_list *ap, int flag)
{
	if (flag == 1 || flag == 2 || flag == 3 || flag == 4 || flag == 7)
		return (pos + 2);
	if (flag == 5)
	{
		pos += 2;
		while (ft_isdigit(format[pos]))
			pos++;
		return (pos + 1);
	}
	if (flag == 6)
	{
		pos++;
		while (ft_isdigit(format[pos]) || format[pos] == '.')
			pos++;
		return (pos + 1);
	}
	return (0);
}

int		ft_printf(const char * restrict format, ...)
{
	va_list ap;
	int		i;
	char *line;
	int flag;

	i = 0;
	flag = -1;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
			flag = reckon_flag(format, i + 1, &ap);
		if (flag != -1 && flag != -2)
		{
			do_print(&ap, flag, i + 1, format);
			i = get_end_flag(format, i, &ap, flag);
			flag = -1;
		}
		else if (flag == -2)
			break ;
		else
			i = print_inter(format + i, i);
	}
	return (0);
}

int		main(int ac, char **av)
{
	//ft_printf(av[1], ft_atoi(av[2]), ft_atoi(av[3]));
	//ft_putstr("\n");
	ft_printf("|%.5d|\n", -123111111111);
	   printf("|%.5d|",   -123111111111);
}
