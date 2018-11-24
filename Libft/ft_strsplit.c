/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:27:13 by agesp             #+#    #+#             */
/*   Updated: 2018/11/12 13:40:39 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countword(const char *s, char c)
{
	int		i;
	int		nbmots;

	i = 0;
	nbmots = 0;
	if (s[i] != '\0')
	{
		while (s[i])
		{
			if (s[i] == c && s[i])
			{
				while (s[i] == (char)c && s[i])
					i++;
				nbmots++;
			}
			i++;
		}
		return (nbmots + 1);
	}
	return (0);
}

static char	**do_split(char const *s, char c, char **myreturn, int countmots)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = -1;
	k = -1;
	while (s[++j] && i < countmots)
	{
		while (s[j] != c)
			myreturn[i][++k] = s[j++];
		myreturn[i][k + 1] = '\0';
		k = -1;
		if (s[j] == c)
		{
			while (s[j] == c)
				j++;
			j--;
			i++;
		}
	}
	myreturn[i] = NULL;
	return (myreturn);
}

static int	check_lenght(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (i == ft_strlen(s))
		return (1);
	return (0);
}

static char	**is_max_lenght(char const *s, char **myreturn)
{
	myreturn[0] = (char*)s;
	myreturn[1] = NULL;
	return (myreturn);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		countmots;
	char	**myreturn;

	if (s)
	{
		i = -1;
		countmots = countword((const char *)s, c);
		if (!(myreturn = (char**)malloc(sizeof(*myreturn) * (countmots + 1))))
			return (NULL);
		while (++i < countmots)
			if (!(myreturn[i] = (char*)malloc(sizeof(char)
							* (ft_strlen(s) + 1))))
				return (NULL);
		i = 0;
		while (s[i] == c)
			i++;
		if (check_lenght(s, c))
			return (is_max_lenght(s, myreturn));
		myreturn = do_split(&s[i], c, myreturn, countmots);
		return (myreturn);
	}
	return (NULL);
}
