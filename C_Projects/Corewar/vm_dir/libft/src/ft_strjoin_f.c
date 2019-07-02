/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfragnou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 19:12:06 by pfragnou          #+#    #+#             */
/*   Updated: 2018/04/03 19:13:26 by pfragnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strjoin_f(char *s1, char *s2, uint8_t opt)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (NULL);
	else if (!s2)
		return (opt & 1 ? s1 : ft_strdup(s1));
	else if (!s1)
		return (opt & 2 ? s2 : ft_strdup(s2));
	if (!(str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	if (opt & 1)
		free(s1);
	if (opt & 2)
		free(s2);
	return (str);
}
