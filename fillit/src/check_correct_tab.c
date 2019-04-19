/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_correct_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:03:41 by agesp             #+#    #+#             */
/*   Updated: 2018/12/13 09:58:53 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	count_char(char *line, int *j, int *h)
{
	int k;
	int sj;
	int sh;

	k = 0;
	sj = *j;
	sh = *h;
	while (line[k])
	{
		if (line[k] == '.')
			sj++;
		if (line[k] == '#')
			sh++;
		k++;
	}
	*j = sj;
	*h = sh;
}

static int	check_tab(char **tab)
{
	int i;
	int j;
	int h;
	int k;

	i = -1;
	j = 0;
	k = 0;
	h = 0;
	while (tab[++i])
	{
		if ((i + 1) % 5 != 0)
		{
			if (!(ft_strlen(tab[i]) == 5))
				return (-1);
			count_char(tab[i], &j, &h);
		}
		else if (ft_strcmp(tab[i], "\n") != 0)
			return (-1);
	}
	if (h == 0 || j == 0 || (i + 1) % 5 != 0)
		return (-1);
	if ((j != 0 && h != 0) && (h % 4 != 0 || j % 12 != 0))
		return (-1);
	return (1);
}

static char	**terminate_tab(char **tab, int i)
{
	if (i >= 130)
		return (NULL);
	while (i < 130)
	{
		tab[i] = NULL;
		i++;
	}
	return (tab);
}

static char	**m_tab(char *save, char **tab, int i, int fd)
{
	while (get_next_line(fd, &save))
	{
		if ((ft_strlen(save) == 4 || ft_strlen(save) == 0))
		{
			if (!(tab[i] = malloc(sizeof(char) * ft_strlen(save) + 1)))
				return (NULL);
			if (ft_strlen(save) == 0)
				tab[i][0] = '\n';
			else
			{
				tab[i] = ft_strcpy(tab[i], save);
				tab[i][4] = '\n';
			}
			i++;
		}
		free(save);
	}
	free(save);
	tab = terminate_tab(tab, i);
	if (tab && check_tab(tab) == 1 && check_entry(tab) == 1 && !close(fd))
		return (tab);
	free_tab(tab);
	return (NULL);
}

char		**make_tab(char *file)
{
	int		i;
	int		fd;
	char	**tab;
	char	*save;

	i = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	save = NULL;
	if ((tab = malloc(sizeof(char*) * 130)) == NULL)
		return (NULL);
	return (m_tab(save, tab, i, fd));
}
