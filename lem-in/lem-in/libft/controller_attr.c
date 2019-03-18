/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_attr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:56:32 by kecosmon          #+#    #+#             */
/*   Updated: 2018/06/01 17:56:35 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "printf/includes/printf.h"

char	*controller_flag(t_parsing *lst, char *str)
{
	if (lst->hash && lst->conv == 'x' && ft_strlen(str) && !lst->zero)
		return (addhexachar(str, 1, "0x"));
	else if (lst->hash && lst->conv == 'x' && ft_strlen(str))
		return (ft_strncpy(str, "0x", 2));
	if (lst->hash && lst->conv == 'X' && ft_strlen(str) && !lst->zero)
		return (addhexachar(str, 1, "0X"));
	else if (lst->hash && lst->conv == 'x' && ft_strlen(str))
		return (ft_strncpy(str, "0X", 2));
	if (lst->hash && (lst->conv == 'o' || lst->conv == 'O')\
		&& !lst->zero && (!lst->prec || lst->prec == -1))
		return (addoctachar(str));
	else if (lst->hash && (lst->conv == 'o' || lst->conv == 'O'))
		return (ft_strncpy(str, "0", 1));
	if (issigned(lst) && lst->max)
	{
		if (str[0] != '-')
			str = straddnchar(str, 0, 1, '+');
	}
	if (issigned(lst) && is_digit(str[0]) && lst->space &&\
		(!lst->prec || lst->decimal > lst->prec))
		str = straddnchar(str, 0, 1, ' ');
	else if (issigned(lst) && is_digit(str[0]) && lst->space)
		str = ft_strncpy(str, " ", 1);
	return (str);
}

char	*controller_decimal(t_parsing *lst, char *str)
{
	int		length;
	int		way;
	char	c;

	c = ' ';
	way = 0;
	if (lst->min)
		way = 1;
	length = ft_strlen(str);
	if (str[0] == '\0' && lst->conv == 'c')
		length = 1;
	if (lst->decimal > length)
		str = straddnchar(str, way, lst->decimal - length, c);
	else if (lst->min > length)
		str = straddnchar(str, way, lst->min - length, c);
	return (str);
}

char	*applyspecialprecision(t_parsing *lst, char *str)
{
	int		sign;
	char	*new;
	int		i;

	if (str[0] == '-' || str[0] == '+')
		sign = 1;
	else
		sign = 0;
	if (lst->prec > (int)ft_strlen(str) - sign)
	{
		new = ft_strnew(lst->prec + sign);
		if (sign)
			new = ft_strncat(new, str, 1);
		i = sign;
		while (i < lst->prec - (int)ft_strlen(str) + 2 * sign)
			new[i++] = '0';
		if (lst->conv == 'c' && str[0] == 0)
			new[--i] = '\0';
		new = ft_strcat(new, &str[sign]);
		freestr(str);
		return (new);
	}
	else
		return (str);
}

char	*controller_prec(t_parsing *lst, char *str)
{
	char	*new;

	if (is_special_prec(lst, str))
		return (applyspecialprecision(lst, str));
	else if ((issigned(lst) || isunsigned(lst) || lst->conv == 'p'))
	{
		if (str[0] == '0' && !str[1] && lst->prec)
		{
			freestr(str);
			return (ft_strdup(""));
		}
		return (str);
	}
	else if ((lst->conv != 'c' && lst->prec > 0 && !lst->hash) ||
			(lst->conv != 'o' && lst->conv != 'O' &&
			lst->prec > 0 && lst->hash))
	{
		new = ft_strncpy(ft_strnew(lst->prec), str, lst->prec);
		freestr(str);
		return (new);
	}
	else
		return (str);
}

char	*controller_attr(t_parsing *lst, char *str)
{
	if (lst->zero)
	{
		if (str[0] == '-' || str[0] == '+' || lst->max)
			lst->zero -= 1;
		lst->prec = lst->zero;
	}
	if (issigned(lst) || isunsigned(lst))
	{
		str = controller_prec(lst, str);
		str = controller_flag(lst, str);
		str = controller_decimal(lst, str);
	}
	else
	{
		if (lst->prec == -1 && lst->conv != '%')
		{
			freestr(str);
			str = ft_strdup("");
		}
		str = controller_prec(lst, str);
		str = controller_decimal(lst, str);
	}
	return (str);
}
