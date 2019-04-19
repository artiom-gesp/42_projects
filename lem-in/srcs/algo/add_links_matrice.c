/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:59:44 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/05 11:13:49 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int					**ft_malloc_matrix(t_lemin *e)
{
	int i;
	int **matrix;

	i = -1;
	if (!(matrix = ft_memalloc(sizeof(int *) * e->nb_rooms)))
		lem_in_error(e, 1);
	while (++i < e->nb_rooms)
		if (!(matrix[i] = ft_memalloc(sizeof(int) * e->nb_rooms)))
			lem_in_error(e, 1);
	return (matrix);
}

int					init_map(t_lemin *e, char *s1, char *s2, long long key2)
{
	long long key1;

	if (ft_strlen(s2) > 30 || ft_strlen(s1) > 30)
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
		lem_in_error(e, 19);
	}
	key1 = generate_hash(s1, e->nb_rooms);
	key2 = generate_hash(s2, e->nb_rooms);
	if (e->h[key1] == NULL || e->h[key2] == NULL)
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
		return (1);
	}
	while (0 != ft_strcmp(e->h[key1]->r->name, s1))
		key1++;
	while (0 != ft_strcmp(e->h[key2]->r->name, s2))
		key2++;
	e->h[key1]->r->nb_links++;
	e->h[key2]->r->nb_links++;
	e->map[e->h[key1]->r->id_r][e->h[key2]->r->id_r] = 1;
	e->map[e->h[key2]->r->id_r][e->h[key1]->r->id_r] = 1;
	return (0);
}

void				links_rooms(t_lemin *e)
{
	t_rooms	*r;
	int		y;
	int		x;
	int		n;

	y = -1;
	while (++y < e->nb_rooms)
	{
		r = e->table_r[y];
		if (!(r->links = ft_memalloc(sizeof(t_rooms) * r->nb_links)))
			lem_in_error(e, 1);
		x = -1;
		n = 0;
		while (++x < e->nb_rooms)
			if (e->map[y][x] == 1)
				r->links[n++] = e->table_r[x];
		n++;
	}
}

int					parsing_links(char *line, t_lemin *e)
{
	int		i;
	char	*s1;
	char	*s2;

	if (!e->map && !(e->map = ft_malloc_matrix(e)))
		lem_in_error(e, 1);
	if (!(i = ft_strichr(line, '-')))
		return (1);
	s1 = name_rooms(e, line, '-');
	if (!(s2 = ft_strdup(&line[++i])))
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
		ft_strdel(&line);
		lem_in_error(e, 1);
	}
	else if (init_map(e, s1, s2, 0))
		return (1);
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (0);
}
