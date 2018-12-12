/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 13:43:22 by agesp             #+#    #+#             */
/*   Updated: 2018/12/12 17:26:45 by agesp            ###   ########.fr       */
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
		i = print_inter(format + i, i);
		if (format[i] == '%')
			flag = reckon_flag(format, i + 1, &ap);
		if (flag != -1)
		{
			do_print(&ap, flag);
			flag = -1;
			i += 2;
		}
	}
	return (0);
}

int		main(int ac, char **av)
{
	//ft_printf(av[1], ft_atoi(av[2]), ft_atoi(av[3]));
	//ft_putstr("\n");
	ft_printf("|%s| |%d| |%c|\n", "coucou", 23, 's');
	printf("|%.5s|\n", "-12gfdgdfgdfg");
}
