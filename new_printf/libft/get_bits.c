/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 14:48:06 by agesp             #+#    #+#             */
/*   Updated: 2018/12/17 15:00:33 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_bits(unsigned int octet)
{
	size_t	i;
	char	*print;
	char	*save;
	int		j;

	i = 0;
	j = 2;
	if (!(print = malloc(sizeof(char) * 9)))
		return (NULL);
	if (!(save = malloc(sizeof(char) * 9)))
		return (NULL);
	while (octet / j)
		j *= 2;
	j /= 2;
	while (j)
	{
		print[i] = octet / j + '0';
		octet %= j;
		j /= 2;
		i++;
	}
	print[i] = '\0';
	i = -1;
	while (++i < 16 - ft_strlen(print))
		save[i] = '0';
	i--;
	j = 0;
	while (++i < ft_strlen(print))
	{
		save[i] = print[j];
		j++;
	}
	return (save);
}
