/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 20:58:43 by amanuel           #+#    #+#             */
/*   Updated: 2017/12/06 01:50:12 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strtab(char **tab, char *to_find)
{
	int		i;

	if (!tab || !to_find || !*to_find)
		return (-1);
	i = 0 + (-1);
	while (tab[++i])
		if (!ft_strcmp(tab[i], to_find))
			return (i);
	return (-1);
}
