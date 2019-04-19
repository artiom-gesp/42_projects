/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_dec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:42:35 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/05 13:29:01 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/includes/printf.h"

void		conv_decimal(va_list arg, t_parsing *lst, int *ret)
{
	intmax_t	dec;
	char		*str;

	str = 0;
	dec = 0;
	dec = controller_spec_mod(lst, arg, dec);
	str = ft_itoa_base(dec, 10, lst);
	str = controller_attr(lst, str);
	strprint(str, ret);
	freestr(str);
}

void		conv_udecimal(va_list arg, t_parsing *lst, int *ret)
{
	uintmax_t	dec;
	char		*str;

	str = 0;
	dec = 0;
	dec = controller_spec_mod_unsinged(lst, arg, dec);
	if (lst->conv == 'x' || lst->conv == 'X')
		str = ft_uitoa_base(dec, 16, lst);
	else if (lst->conv == 'o' || lst->conv == 'O')
		str = ft_uitoa_base(dec, 8, lst);
	else if (lst->conv == 'u' || lst->conv == 'U')
		str = ft_uitoa_base(dec, 10, lst);
	else if (lst->conv == 'b')
		str = ft_itoa_base((uintmax_t)dec, 2, lst);
	str = controller_attr(lst, str);
	strprint(str, ret);
	freestr(str);
}

static char	*spec_void_p(t_parsing *lst, char *str)
{
	lst->prec = lst->zero;
	str = controller_prec(lst, str);
	str = controller_decimal(lst, str);
	str = addhexachar(str, 0, "0x");
	return (str);
}

void		conv_void_p(va_list arg, t_parsing *lst, int *ret)
{
	char		*str;
	uintmax_t	p;

	str = 0;
	p = (uintmax_t)va_arg(arg, uintmax_t);
	str = ft_uitoa_base(p, 16, lst);
	if (lst->zero && str[0] != '0')
		str = spec_void_p(lst, str);
	else if (lst->zero)
	{
		lst->prec = lst->zero;
		str = controller_prec(lst, str);
		str = controller_decimal(lst, str);
		str = ft_strncpy(str, "0x", 2);
	}
	else
	{
		str = controller_prec(lst, str);
		str = addhexachar(str, 0, "0x");
		str = controller_decimal(lst, str);
	}
	strprint(str, ret);
	freestr(str);
}

void		conv_int_p(va_list arg, t_parsing *lst, int *ret)
{
	int	*pi;
	int	i;

	i = 0;
	if (lst)
		i = 0;
	pi = va_arg(arg, int *);
	*pi = *ret;
}
