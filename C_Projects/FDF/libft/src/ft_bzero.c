/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:38:29 by agesp             #+#    #+#             */
/*   Updated: 2018/12/18 11:15:09 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*save;

	i = 0;
	save = s;
	if (n == 0)
		return ;
	while (i < n)
	{
		save[i] = '\0';
		i++;
	}
	s = save;
}
