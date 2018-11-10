/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:27:13 by agesp             #+#    #+#             */
/*   Updated: 2018/11/09 18:16:54 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	readstart(char const *s, char c, int startorend)
{
	int		i;

	if (startorend == 1)
	{
		i = 0;
		while (s[i] == c)
			i++;
		return (i);
	}
	else
	{
		i = ft_strlen(s) - 1;
		while (s[i] == c)
			i--;
		return (i);
	}
}

static char	*ft_strtrimop(char const *s, char c, int start, int end)
{
	int i;
	char *save;

	i = 0;
	if (readstart(s, c, 1) == readstart(s, c, 2) && s[0] != '\0')
	{
		save = malloc(sizeof(char) * 2);
		save[0] = s[readstart(s, c, 1)];
		save[1] = '\0';
		return (save);
	}
	if (start >= end)
	{
		save = ft_memalloc(1);
		return (save);
	}
	if (!(save = (char*)malloc(sizeof(char) * (end - start + 2))))
		return (NULL);
	while (start <= end)
		save[i++] = s[start++];
	save[i] = '\0';
	return (save);
}

static int		countword(char *s, char c)
{
	int i;
	int nbmots;

	i = 0;
	nbmots = 0;
	if(s[i] != '\0')
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

char	**do_split(char const *s, char c, char **myreturn, int countmots)
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

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		countmots;
	char	**myreturn;

	if (s)
	{
		i = -1;
		countmots = countword(ft_strtrimop(s, c, readstart(s, c, 1), 
					readstart(s, c, 2)), c);
		if (!(myreturn = (char**)malloc(sizeof(char*) * (countmots + 1))))
			return (NULL);
		while (++i < countmots)
			if (!(myreturn[i] = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
				return (NULL);
		i = 0;

		while (s[i] == c)
			i++;
		myreturn = do_split(&s[i], c, myreturn, countmots);
		return(myreturn);
	}
	return (NULL);
}
