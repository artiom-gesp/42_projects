/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:42:35 by kecosmon          #+#    #+#             */
/*   Updated: 2018/06/01 17:42:37 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/includes/printf.h"

const char	*ft_writecoclor(char *str, const char *format, int nb)
{
	ft_putstr(str);
	while (nb)
	{
		format++;
		nb--;
	}
	return (format);
}

void		check_color(const char **format)
{
	if (!ft_strncmp(*format, "{RED}", 5))
		*format = ft_writecoclor(RED, *format, 5);
	else if (!ft_strncmp(*format, "{BLUE}", 6))
		*format = ft_writecoclor(BLUE, *format, 6);
	else if (!ft_strncmp(*format, "{CYAN}", 6))
		*format = ft_writecoclor(CYAN, *format, 6);
	else if (!ft_strncmp(*format, "{PURPLE}", 8))
		*format = ft_writecoclor(PURPLE, *format, 8);
	else if (!ft_strncmp(*format, "{YELLOW}", 8))
		*format = ft_writecoclor(YELLOW, *format, 8);
	else if (!ft_strncmp(*format, "{GREEN}", 7))
		*format = ft_writecoclor(GREEN, *format, 7);
	else if (!ft_strncmp(*format, "{EOC}", 5))
		*format = ft_writecoclor(EOC, *format, 5);
}

static int	controller_printf(va_list arg, const char *format, int ret)
{
	t_parsing *lst;

	while (*format)
	{
		lst = (t_parsing *)malloc(sizeof(t_parsing));
		lst = init_lst(lst);
		if (*format == '{')
			check_color(&format);
		if (*format == '%')
			format = glob_init(arg, format + 1, &ret, lst);
		else if (*format)
			format = ft_print(format, &ret);
		free(lst);
	}
	return (ret);
}

static int	check_printf(va_list arg, const char *format, int ret)
{
	char *str;

	str = (ft_strchr(format, '%'));
	if (!format)
		return (-1);
	else if (str && !format[1])
		return (0);
	else if (!str)
	{
		ft_print((char *)format, &ret);
		return (ret);
	}
	else
		return (controller_printf(arg, format, ret));
}

int			ft_printf(const char *format, ...)
{
	va_list arg;
	int		ret;

	ret = 0;
	va_start(arg, format);
	ret = check_printf(arg, format, ret);
	va_end(arg);
	return (ret);
}
