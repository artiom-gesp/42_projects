/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 11:58:11 by agesp             #+#    #+#             */
/*   Updated: 2019/01/07 09:34:54 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	remove_flag(t_plist *list)
{
	int		i;
	int		zero;
	int		space;
	int		minus;
	int		plus;

	i = 0;
	zero = ft_strchr(list->sign, '0') ? 1 : 0;
	plus = ft_strchr(list->sign, '+') ? 1 : 0;
	minus = ft_strchr(list->sign, '-') ? 1 : 0;
	space = ft_strchr(list->sign, ' ') ? 1 : 0;
	while (i < 4)
	{
		if (minus && zero && list->sign[i] == '0')
			list->sign[i] = 'z';
		if (plus && space && list->sign[i] == ' ')
			list->sign[i] = 'z';
		if ((list->precision > 0 || list->precision == -1)
				&& list->sign[i] == '0' && list->flag != 'f')
			list->sign[i] = 'z';
		i++;
	}
}

void	sort_flags(t_plist *list, char flag)
{
	char c;

	list->flag = flag;
	c = list->flag;
	if (c == 'D' || c == 'U' || c == 'O')
		list->conversion = 2;
	if (c == 'S' || c == 'C' || c == 'D' || c == 'U'
			|| c == 'O' || c == 'F')
		list->flag += 32;
}
