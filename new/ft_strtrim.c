/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:26:13 by agesp             #+#    #+#             */
/*   Updated: 2018/11/12 09:42:10 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	readstart(const char *s)
{
	int		i;

	i = 0;
	while (s[i] == '\t' || s[i] == '\n' || s[i] == ' ')
		i++;
	return (i);
}

static int	readend(const char *s)
{
	int		i;

	i = ft_strlen(s) - 1;
	while (s[i] == '\t' || s[i] == '\n' || s[i] == ' ')
		i--;
	return (i);
}

static char	*getstring(const char *s, int start, int end)
{
	int		i;
	char	*save;

	i = 0;
	if (start >= end)
	{
		save = ft_memalloc(1);
		return (save);
	}
	if (end - start == 1)
		return (char*)(&s[start]);
	if (!(save = (char*)malloc(sizeof(char) * (end - start + 2))))
		return (NULL);
	while (start <= end)
	{
		save[i] = s[start];
		start++;
		i++;
	}
	save[i] = '\0';
	return (save);
}

char		*ft_strtrim(char const *s)
{
	char	*save;

	save = malloc(sizeof(char));
	if (s)
	{
		if (readstart(s) == readend(s) && s[0] != '\0')
		{
			save[0] = s[readstart(s)];
			save[1] = '\0';
			return (save);
		}
		return (getstring(s, readstart(s), readend(s)));
	}
	return (NULL);
}
