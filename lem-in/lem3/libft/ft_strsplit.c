/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:19:04 by kecosmon          #+#    #+#             */
/*   Updated: 2019/02/22 15:19:05 by kecosmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nblin(char const *s, char c)
{
	size_t i;
	size_t nblin;
	size_t lens;
	size_t tempcompt;

	i = 0;
	nblin = 0;
	lens = ft_strlen(s) - 1;
	while (s[i] == c)
		i++;
	while (s[lens] == c)
		lens--;
	if (s[i] >= 32 && s[i] <= 126)
		nblin++;
	while (s[i++] != '\0' && i < lens)
	{
		tempcompt = 0;
		while (s[i] == c)
		{
			if (tempcompt++ == 0)
				nblin++;
			i++;
		}
	}
	return (nblin);
}

static size_t	ft_removecfin(char const *s, char c)
{
	size_t i;

	i = ft_strlen(s) - 1;
	while (s[i] == c && i > 0)
		i--;
	return (i);
}

static size_t	ft_lenlin(char const *s, char c, size_t compt)
{
	size_t lenlin;

	lenlin = 0;
	while (s[compt] >= 32 && s[compt] <= 126 && s[compt] != c)
	{
		lenlin++;
		compt++;
	}
	return (lenlin);
}

static size_t	ft_strsplit2(char const *s, char c, char **tabs, size_t lintabs)
{
	size_t i;
	size_t coltabs;

	i = 0;
	while (s[i] == c)
		i++;
	while (s[i] != '\0' && i <= ft_removecfin(s, c))
	{
		while (s[i] == c)
			i++;
		coltabs = 0;
		while (s[i] != c && s[i] != '\0')
		{
			tabs[lintabs][coltabs] = s[i];
			coltabs++;
			i++;
		}
		tabs[lintabs][coltabs] = '\0';
		lintabs++;
	}
	return (lintabs);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	lintabs;
	size_t	compt;
	char	**tabs;

	if (!s)
		return (NULL);
	i = 0;
	lintabs = 0;
	compt = 0;
	tabs = (char **)malloc((ft_nblin(s, c) + 1) * sizeof(*tabs));
	while (i < (ft_nblin(s, c) + 1))
	{
		while (s[compt] == c)
			compt++;
		tabs[i] = (char *)malloc((ft_lenlin(s, c, compt) + 1) * sizeof(tabs));
		compt = compt + ft_lenlin(s, c, compt);
		i++;
	}
	if (tabs == NULL)
		return (NULL);
	lintabs = ft_strsplit2(s, c, tabs, lintabs);
	tabs[lintabs] = NULL;
	return (tabs);
}
