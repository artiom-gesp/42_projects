/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_w.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 15:54:23 by agesp             #+#    #+#             */
/*   Updated: 2018/12/18 17:11:00 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	w_print_char(wchar_t c)
{
	if (c <= 0x7f)
		ft_putchar(c);
	else if (c <= 0x7ff)
	{
		ft_putchar((c >> 6) | 0xc0);
		ft_putchar((c & 0x3f) | 0x80);
	}
	else if (c <= 0xffff)
	{
		ft_putchar((c >> 12) | 0xe0);
		ft_putchar(((c >> 6) & 0x3f) | 0x80);
		ft_putchar((c & 0x3f) | 0x80);
	}
	else if (c <= 0x10ffff)
	{
		ft_putchar((c >> 18) | 0xf0);
		ft_putchar(((c >> 12) & 0x3f) | 0x80);
		ft_putchar(((c >> 6) & 0x3f) | 0x80);
		ft_putchar((c & 0x3f) | 0x80);
	}
}

void	w_print_str(wchar_t *s)
{
	while (*s)
		w_print_char(*s++);
}
