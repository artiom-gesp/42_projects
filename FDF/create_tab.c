/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 10:49:28 by agesp             #+#    #+#             */
/*   Updated: 2019/01/23 13:04:16 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			get_tab_len(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int			is_tab_ok(char **tab, int x)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (!ft_isdigit(tab[i][0]) && (tab[i][0] != '-'
					&& tab[i][1] && !ft_isdigit(tab[i][1])))
			return (0);
		if (tab[i][0] == '-' && !ft_isdigit(tab[i][1]))
			return (0);
		i++;
	}
	if (i != x && x != -1)
		return (0);
	return (1);
}

void		copy_into_tab(int tab[5000][5000], char **tab2)
{
	int			i;
	static int	y = 0;

	i = 0;
	while (tab2[i])
	{
		tab[i][y] = ft_atoll(tab2[i]);
		i++;
	}
	y++;
}

static void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int			create_tab(char *file, t_fstruct *p)
{
	char	*line;
	int		fd;
	char	**tab;

	if ((fd = open(file, O_RDONLY)) < 1)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit(line, ' ');
		if (!is_tab_ok(tab, p->x))
		{
			free(line);
			free_tab(tab);
			return (0);
		}
		p->x = get_tab_len(tab);
		copy_into_tab(p->tab, tab);
		free_tab(tab);
		p->y++;
		free(line);
	}
	free(line);
	close(fd);
	return (1);
}
