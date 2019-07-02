/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 12:48:16 by amanuel           #+#    #+#             */
/*   Updated: 2018/12/21 07:43:49 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*fresh;

	if (!(fresh = malloc(size)))
	{
		write(1, "Echec de memmalloc\n", 19);
		exit(-1);
	}
	ft_memset(fresh, 0, size);
	return (fresh);
}
