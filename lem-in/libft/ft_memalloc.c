/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:26:19 by kecosmon          #+#    #+#             */
/*   Updated: 2019/02/22 15:26:21 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char *zonemem;

	zonemem = (char *)malloc(size * sizeof(zonemem));
	if (zonemem == NULL)
		return (NULL);
	bzero(zonemem, size);
	return (zonemem);
}
