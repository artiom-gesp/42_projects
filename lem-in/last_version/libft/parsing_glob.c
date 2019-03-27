/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_glob.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:42:35 by kecosmon          #+#    #+#             */
/*   Updated: 2018/06/01 17:42:37 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/includes/printf.h"
#include "printf/includes/conver.h"

void	parsing_conv(va_list arg, t_parsing *lst, int *ret)
{
	int i;

	i = 0;
	while (i < 17)
	{
		if (g_convtab[i].check == lst->conv)
			(g_convtab[i].f)(arg, lst, ret);
		i++;
	}
}
