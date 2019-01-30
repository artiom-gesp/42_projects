/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:27:13 by agesp             #+#    #+#             */
/*   Updated: 2019/01/21 10:44:14 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static int	countword(const char *s, char c)
{
	int i;
	int nbmots;

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

static char	*get_next_word(char const *s, char c)
{
	int		size_word;
	char	*str;

	size_word = get_size(s, c);
	str = NULL;
	if (!(str = ft_strnew(size_word)))
		return (NULL);
	str = ft_strncpy(str, s, size_word);
	return (str);
}

static void	get_var(int *i, int *j)
{
	*j = 0;
	*i = 0;
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		words;
	char	**tab;
	int		j;

	if (!s)
		return (NULL);
	get_var(&i, &j);
	words = countword(s, c);
	if (!(tab = (char**)malloc(sizeof(char*) * (words))))
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			tab[j++] = get_next_word(&s[i], c);
			i += get_size(&s[i], c);
		}
		else
			i++;
	}
	tab[j] = 0;
	return (tab);
}
