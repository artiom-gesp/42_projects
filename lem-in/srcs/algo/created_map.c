/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   created_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:59:44 by kecosmon          #+#    #+#             */
/*   Updated: 2019/03/21 14:36:36 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lemin.h"

void	created_liasion_map(int **map, t_lemin *e)
{
	int y;

	y = 0;
	while (y < e->nb_rooms)
	{
		map[y][y] = 2;
		y++;
	}
}

void	copy_to_tab(t_lemin *e, t_links *l)
{
	int x;
	int key1;
	int key2;
	int i;

	x = 0;
	i = 0;
	while (i < e->nb_rooms)
	{
		x = 0;
		while (x < e->nb_rooms)
			e->map[i][x++] = 0;
		i++;
	}
	while (l)
	{
		key2 = generate_hash(l->s2, e->nb_rooms);
		key1 = generate_hash(l->s1, e->nb_rooms);
		while (ft_strcmp(l->s2, e->h[key2]->r->name))
			key2++;
		while (ft_strcmp(l->s1, e->h[key1]->r->name))
			key1++;
		e->map[e->h[key1]->r->nb_rooms][e->h[key2]->r->nb_rooms] = 1;
		e->map[e->h[key2]->r->nb_rooms][e->h[key1]->r->nb_rooms] = 1;
		l = l->next;
	}
}

void	created_map(t_lemin *e)
{
	int			**map;
	t_rooms		*r;
	t_links		*l;
	int			i;

	i = 0;
	r = e->r;
	l = e->l;
	if (!(map = malloc(sizeof(int *) * e->nb_rooms)))
		exit(-1);
	while (i < e->nb_rooms)
	{
		if (!(map[i] = malloc(sizeof(int) * e->nb_rooms)))
			exit(-1);
		i++;
	}
	e->map = map;
	copy_to_tab(e, l);
}
