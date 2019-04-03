/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:37:44 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/02 17:09:04 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		error_messages(int error)
{
	error == 1 ? write(1, "Error: malloc failure\n", 22) : 0;
	error == 2 ? write(1, "Error: ' ' or '-' before or after ants\n", 39) : 0;
	error == 3 ? write(1, "Error: negative, too many, or no ants\n", 38) : 0;
	error == 4 ? write(1, "Error: comment after ##start or ##end\n", 38) : 0;
	error == 5 ? write(1, "Error: ants badly formatted\n", 28) : 0;
	error == 6 ? write(1, "Error: room starts with 'L' or '#'\n", 35) : 0;
	error == 7 ? write(1, "Error: more than 1 start or end room\n", 37) : 0;
	error == 8 ? write(1, "Error: start or end\n", 23) : 0;
	error == 10 ? write(1, "Error: room links to self\n", 27) : 0;
	error == 11 ? write(1, "Error: no rooms\n", 17) : 0;
	error == 12 ? write(1, "Error: no links or empty map\n", 29) : 0;
	error == 13 ? write(1, "Error: no path\n", 15) : 0;
	error == 14 ? write(1, "Error: link to unknown room\n", 28) : 0;
	error == 15 ? write(1, "Error: coordinates\n", 31) : 0;
	error == 16 ? write(1, "Error: duplicate rooms\n", 23) : 0;
	error == 18 ? write(1, "Error: too many arguments\n", 26) : 0;
}

void			free_ants(t_lemin *e)
{
	t_ants *a;

	while (e->a)
	{
		a = e->a;
		e->a = e->a->next;
		free(a);
	}
}

void			path_fun_free(t_lemin *e)
{
	if (e->p)
		free_path(e->p, 0);
	if (e->find_new)
	{
		free(e->stack);
		free(e->map_stack);
		free(e->find_new);
		free(e->map_fn);
		free(e->prev);
		free(e->map_prev);
		free(e->map_visited);
	}
}

void			free_info(t_lemin *e)
{
	t_info *i;

	while (e->i)
	{
		i = e->i;
		e->i = e->i->next;
		if (i->line)
			free(i->line);
		free(i);
	}
}

void			lem_in_error(t_lemin *e, int error)
{
	int i;

	i = -1;
	if (error > 0)
		error_messages(error);
	else if (error != -2)
		write(1, "Error\n", 6);
	if (e->i)
		free_info(e);
	if (e->map)
	{
		while (++i < e->nb_rooms)
			free(e->map[i]);
		free(e->map);
	}
	if (e->r)
		while (e->r && (e->r = e->r->next))
		{
			ft_strdel(&(e->r->name)); //TO_FREE !!!
			free(e->r->links);
		}
	path_fun_free(e);
	free_ants(e);
	free(e);
	if (error == -2)
		exit(1);
	exit(0);
}

int			main(int ac, char const *av[])
{
	t_lemin *e;

	if ((!(e = ft_memalloc(sizeof(t_lemin)))))
		lem_in_error(e, 1);
	if (ac < 1 && av)
	{
		ft_putstr("usage: lem-in ,[maps...]");
		return (0);
	}
	reader(e);
	setup_map(e);
	e->max_lines = get_len(e);
	move_ants_forward(e);
	ft_printf("\n\nsent %d ants through %d paths in %d steps\n",\
			e->nb_ants, e->nb_paths, \
			e->p->size_path == 2 ? 1 : e->max_lines);
	lem_in_error(e, -2);
	return (0);
}
