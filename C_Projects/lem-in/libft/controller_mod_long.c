/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_mod_long.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:42:35 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/05 13:28:32 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/includes/printf.h"

intmax_t		controller_spec_mod(t_parsing *lst, va_list arg, intmax_t dec)
{
	if (lst->j)
		dec = va_arg(arg, intmax_t);
	else if (lst->ll)
		dec = (intmax_t)va_arg(arg, long long int);
	else if (lst->l || lst->conv == 'D')
		dec = (intmax_t)va_arg(arg, long int);
	else if (lst->z)
		dec = (intmax_t)va_arg(arg, size_t);
	else if (lst->hh)
		dec = (intmax_t)(signed char)va_arg(arg, int);
	else if (lst->h)
		dec = (intmax_t)(short)va_arg(arg, int);
	else if (lst->conv != 'c')
		dec = (intmax_t)va_arg(arg, int);
	return (dec);
}

uintmax_t		controller_spec_mod_unsinged(t_parsing *lst, va_list arg,\
				uintmax_t dec)
{
	if (lst->j)
		dec = va_arg(arg, uintmax_t);
	else if (lst->ll)
		dec = (uintmax_t)va_arg(arg, unsigned long long int);
	else if (lst->l || lst->conv == 'U' || lst->conv == 'O')
		dec = (uintmax_t)va_arg(arg, unsigned long int);
	else if (lst->z)
		dec = (uintmax_t)va_arg(arg, ssize_t);
	else if (lst->hh)
		dec = (uintmax_t)(unsigned char)va_arg(arg, int);
	else if (lst->h)
		dec = (uintmax_t)(unsigned short int)va_arg(arg, int);
	else
		dec = (uintmax_t)va_arg(arg, unsigned int);
	return (dec);
}
