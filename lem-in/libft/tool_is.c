/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_is.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:42:35 by kecosmon          #+#    #+#             */
/*   Updated: 2018/06/01 17:42:37 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/includes/printf.h"

int		isunsigned(t_parsing *lst)
{
	return (lst->conv == 'O' || lst->conv == 'o' ||\
			lst->conv == 'X' || lst->conv == 'x' ||\
			lst->conv == 'u' || lst->conv == 'U');
}

int		issigned(t_parsing *lst)
{
	return (lst->conv == 'i' || lst->conv == 'd' || lst->conv == 'D');
}

int		is_digit(int c)
{
	return ((char)c >= '0' && (char)c <= '9');
}

int		isocta(t_parsing *lst)
{
	return (lst->conv == 'o' || lst->conv == 'O');
}

int		ishexa(t_parsing *lst)
{
	return (lst->conv == 'x' || lst->conv == 'X');
}
