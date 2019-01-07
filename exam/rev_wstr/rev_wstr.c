/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 17:04:58 by agesp             #+#    #+#             */
/*   Updated: 2019/01/07 17:05:00 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int		count_mots(char *str)
{
	int i;
	int j;

	i = 0;
	if (str[0] != '\0')
		j = 1;
	else
		return (0);
	while (str[i])
	{
		if (str[i] == ' ')
			j++;
		i++;
	}
	return (j);
}

char	**my_alloc(char *str)
{
	int		i;
	int		mots;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	while (str[i])
	{
		i++;
		j++;
	}
	mots = count_mots(str);
	i = -1;
	if (!(tab = (char**)malloc(sizeof(char*) * (mots) + 1)))
		return (0);
	while (++i < mots)
		if (!(tab[i] = (char*)malloc(sizeof(char) * j)))
			return (0);
	return (tab);
}

char	**rev_wstr(char *str)
{
	int		i;
	int		mots;
	int		j;
	char	**tab;

	tab = my_alloc(str);
	mots = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] != ' ' && str[i])
		{
			tab[mots][j++] = str[i++];
		}
		tab[mots][j] = '\0';
		if (str[i] == ' ')
		{
			i++;
			mots++;
			j = 0;
		}
	}
	tab[mots + 1] = NULL;
	return (tab);
}

int		main(int ac, char **av)
{
	int		i;
	char	**tab;

	i = 0;
	if (ac == 2 && av[1][0] != '\0')
	{
		tab = rev_wstr(av[1]);
		while (tab[i])
		{
			i++;
		}
		i--;
		while (i >= 0)
		{
			ft_putstr(tab[i]);
			if (i != 0 && tab)
				write(1, " ", 1);
			i--;
		}
	}
	write(1, "\n", 1);
	return (0);
}
