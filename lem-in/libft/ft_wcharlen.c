/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:29:22 by kecosmon          #+#    #+#             */
/*   Updated: 2018/06/01 17:31:38 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_wcharlen(wchar_t c)
{
	if (c <= 0x7F)
		return (1);
	else if (c <= 0x7FF)
	{
		return (2);
	}
	else if (c <= 0xFFFF)
	{
		return (3);
	}
	else if (c <= 0x10FFFF)
	{
		return (4);
	}
	return (-1);
}
