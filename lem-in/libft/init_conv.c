/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 17:42:35 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/05 13:31:30 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/includes/printf.h"

static t_parsing	*change_conv(t_parsing *lst)
{
	if (lst->conv == 'c' && lst->l)
		lst->conv = 'C';
	if (lst->conv == 's' && lst->l)
		lst->conv = 'S';
	return (lst);
}

int					init_conv(const char **format, t_parsing **lst)
{
	const char	*tmp_format;
	const char	conv[18] = "sSdDioOuUxXcCnp%br";
	int			x;
	t_parsing	*ptr;

	ptr = *lst;
	x = 0;
	tmp_format = *format;
	while (conv[x])
	{
		if (conv[x] == *tmp_format)
		{
			ptr->conv = *tmp_format;
			tmp_format++;
			*format = tmp_format;
			ptr = change_conv(ptr);
			*lst = ptr;
			return (1);
		}
		else
			x++;
	}
	return (0);
}
