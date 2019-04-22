/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_wstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:42:35 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/05 13:28:39 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/includes/printf.h"

wchar_t		*wstraddnchar(wchar_t *wstr, int check, int n, char c)
{
	int		i;
	int		length;
	wchar_t	*new;

	length = ft_wcslen(wstr);
	new = ft_wcsnew(length + n);
	i = 0;
	if (check)
	{
		new = ft_wcscpy(new, wstr);
		while (i < n)
			new[length + i++] = (wchar_t)c;
	}
	else
	{
		while (i < n)
		{
			new[i] = c;
			i++;
		}
		new = ft_wcscat(new, wstr);
	}
	freewstr(wstr);
	return (new);
}

wchar_t		*applywidthwchar(t_parsing *lst, wchar_t *wstr)
{
	int		length;
	int		check;
	char	c;

	c = ' ';
	check = 0;
	if (lst->min)
		check = 1;
	else if (lst->zero)
		c = '0';
	length = ft_wstrlen(wstr);
	if (lst->decimal > length)
		wstr = wstraddnchar(wstr, check, lst->decimal - length, c);
	else if (lst->zero > length)
		wstr = wstraddnchar(wstr, check, lst->zero - length, c);
	else if (lst->min > length)
		wstr = wstraddnchar(wstr, check, lst->min - length, c);
	return (wstr);
}

wchar_t		*applyprecisionwchar(t_parsing *lst, wchar_t *wstr)
{
	wchar_t *new;
	int		i;
	int		octets;

	if (lst->prec)
	{
		new = ft_wcsnew(lst->prec);
		octets = 0;
		i = 0;
		while (wstr[i] && octets + ft_wcharlen(wstr[i]) <= lst->prec)
		{
			new[i] = wstr[i];
			octets += ft_wcharlen(wstr[i]);
			i++;
		}
		new[i] = '\0';
		freewstr(wstr);
	}
	else
		new = wstr;
	return (new);
}
