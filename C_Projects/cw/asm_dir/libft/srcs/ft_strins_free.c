/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanuel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 03:28:45 by amanuel           #+#    #+#             */
/*   Updated: 2019/04/15 20:03:09 by amanuel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strins_free(char *s1, char *s2, short i, char two_bits_free)
{
	char		*fresh;

	fresh = ft_strndup(s1, i);
	fresh = ft_strjoin_free(fresh, s2, two_bits_free);
	fresh = ft_strjoin_free(fresh, s1 + i, 0);
	if (two_bits_free / 2 && s1)
		free(s1);
	return (fresh);
}
