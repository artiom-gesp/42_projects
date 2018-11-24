/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:58:10 by agesp             #+#    #+#             */
/*   Updated: 2018/11/24 17:42:23 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fillit.h"
#include <stdio.h>

int		baobab(char **tab, int i, int j , int h, int k)
{
	while (tab[i])
	{
		if ((i + 1) % 5 != 0)
		{
			k = 0;
			if (!(ft_strlen(tab[i]) == 5))
				return (-1);
			while (tab[i][k])
			{
				if (tab[i][k] == '.')
					j++;
				if (tab[i][k] == '#')
					h++;
				k++;
			}
		}
		else
			if (ft_strcmp(tab[i], "\n") != 0)
				return (-2);
		i++;
	}
	if ((j != 0 && h != 0) && (h % 4 != 0 || j % 12 != 0))
		return (-3);

	return (1);
}

int		check_tab(char **tab)
{
	int i;
	int j;
	int h;
	int k;

	i = 0;
	j = 0;
	k = 0;
	h = 0;
	return (baobab(tab, i, j, h, k));
}

char	**make_tab(char *file)
{
	int		i;
	char	*save;
	int		fd;
	char **tab;

	i = 0;
	fd = open(file, O_RDONLY);
	tab = malloc(sizeof(char*) * 130);
	while (get_next_line(fd, &save))
	{
		if ((ft_strlen(save) == 4 || ft_strlen(save) == 0) && i <= 130)
		{
			tab[i] = ft_strjoin(save, "\n");
			i++;
		}
		else
			return (NULL);
	}
	tab[i] = NULL;
	if (check_tab(tab) == 1)
		return (tab);
	return (NULL);
}
