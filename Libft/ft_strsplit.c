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

static int	readstart(char const *s, char c)
{
	int		i;

	i = 0;
	while (s[i] == c)
		i++;
	return (i);
}

static int	readend(char const *s, char c)
{
	int		i;

	i = ft_strlen(s) - 1;
	while (s[i] == c)
		i--;
	return (i);
}

static char	*ft_strtrimop(char const *s, char c, int start, int end)
{
	int i;
	char *save;

	i = 0;
	if (readstart(s, c) == readend(s, c) && s[0] != '\0')
	{
		save = malloc(sizeof(char) * 2);
		save[0] = s[readstart(s, c)];
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
	while (s[i])
	{
		if (s[i] != c && s[i])
		{
			while (s[i] != (char)c && s[i])
				i++;
			nbmots++;
		}
		i++;
	}
	return (nbmots);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		countmots;
	char	**myreturn;

	if (s)
	{
		i = -1;
		j = -1;
		countmots = countword(ft_strtrimop(s, c, readstart(s, c), readend(s, c)), c);
		if (!(myreturn = (char**)malloc(sizeof(char*) * countmots)))
			return (NULL);
		while (++i < countmots)
			myreturn[i] = (char*)malloc(sizeof(char) * 100);
		i = 0;
		while (s[++j])
		{
			while (s[++j] != c && s[j])
				myreturn[i][j] = s[j];
			if (s[j] == c)
			{
				while (s[j++] == c)
					j++;
				i++;
			}
		}
	}
	return (myreturn);
}

int	main(int ac, char **av)
{
	int i = 0;
	char  **tab = ft_strsplit(av[1], av[2][0]);
	printf("%s\n", ft_strtrimop(av[1], av[2][0], readstart(av[1], av[2][0]), readend(av[1], av[2][0])));
	printf("%d\n", countword(ft_strtrimop(av[1], av[2][0], readstart(av[1], av[2][0]), readend(av[1], av[2][0])), av[2][0]));
/*	while (i < 2)
	{
		printf("%s\n", tab[i]);
		i++;
	}*/
	printf("%s\n", tab[1]);
}



