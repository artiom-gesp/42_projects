/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 16:28:34 by agesp             #+#    #+#             */
/*   Updated: 2018/12/12 17:25:37 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft/libft.h"
# include <stdio.h>

void	do_print(va_list *ap, int flag);
int		reckon_flag(const char *format, int pos, va_list *ap);

void	do_print_dot(va_list *ap, int flag, int digit);
int		reckon_dot(const char *format, int pos, va_list *ap);

#endif
