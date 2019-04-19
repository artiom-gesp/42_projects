/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   created_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:59:44 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/09 09:49:10 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

long long		generate_hash(char *str, int nb_rooms)
{
	int			i;
	long long	key;

	key = 0;
	i = 0;
	while (str[i])
		key += (key * 22) + str[i++];
	key %= 100 * nb_rooms;
	return (key);
}

static t_hash	*created_lst_hash(t_lemin *e, t_rooms *r)
{
	t_hash	*new;

	if (!(new = ft_memalloc(sizeof(t_hash))))
		lem_in_error(e, 1);
	new->r = r;
	return (new);
}

static void		init_hash(t_lemin *e)
{
	t_rooms		*r;
	int			key;

	key = 0;
	r = e->r;
	while (r)
	{
		key = generate_hash(r->name, e->nb_rooms);
		if (key < 0)
			lem_in_error(e, 19);
		if (e->h[key])
			while (e->h[key])
				key++;
		e->h[key] = created_lst_hash(e, r);
		r = r->next;
	}
}

t_rooms			**table_rooms(t_lemin *e)
{
	t_rooms		**r;
	int			i;
	t_rooms		*ro;

	ro = e->r;
	i = 0;
	if (!(r = ft_memalloc(sizeof(t_rooms) * e->nb_rooms)))
		lem_in_error(e, 1);
	while (i < e->nb_rooms)
	{
		r[i] = ro;
		ro = ro->next;
		i++;
	}
	r[i] = NULL;
	return (r);
}

void			created_hastable(t_lemin *e)
{
	int i;

	i = 0;
	if (!(e->h = ft_memalloc(sizeof(t_hash*) * e->nb_rooms * 10000)))
		lem_in_error(e, 1);
	init_hash(e);
}
