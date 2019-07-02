/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 15:13:21 by amanuel           #+#    #+#             */
/*   Updated: 2018/09/26 00:50:34 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strndel(char **data, size_t len)
{
	char	*buff;

	buff = NULL;
	if (!data || len < 1)
		return ;
	if (len >= ft_strlen(*data))
	{
		ft_strclr(*data);
		return ;
	}
	if (!(buff = ft_strdup(*data + len)))
		return ;
	ft_memdel((void*)data);
	if (!(*data = ft_strdup(buff)))
		return ;
	ft_memdel((void*)&buff);
}
