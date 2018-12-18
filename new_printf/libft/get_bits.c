/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bits.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 12:19:04 by agesp             #+#    #+#             */
/*   Updated: 2018/12/18 13:56:51 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*do_bits(unsigned int octet, char *print, char *save, int j)
{
	size_t	i;

	i = 0;
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
	while (++i < 16)
		save[i] = print[j++];
	free(print);
	return (save);
}

char	*get_bits(unsigned int octet)
{
	char	*print;
	char	*save;
	int		j;

	j = 2;
	if (!(print = malloc(sizeof(char) * 17)))
		return (NULL);
	if (!(save = malloc(sizeof(char) * 17)))
		return (NULL);
	return (do_bits(octet, print, save, j));
}
