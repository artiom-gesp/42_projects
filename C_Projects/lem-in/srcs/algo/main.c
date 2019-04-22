/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:37:44 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/08 14:13:17 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		error_messages(int error)
{
	error == 1 ? ft_printf("Error: malloc failure\n") : 0;
	error == 2 ? ft_printf("Error: ' ' or '-' before or after ants\n") : 0;
	error == 3 ? ft_printf("Error: negative, too many, or no ants\n") : 0;
	error == 4 ? ft_printf("Error: comment after ##start or ##end\n") : 0;
	error == 5 ? ft_printf("Error: ants badly formatted\n") : 0;
	error == 6 ? ft_printf("Error: room starts with 'L' or '#'\n") : 0;
	error == 7 ? ft_printf("Error: more than 1 start or end room\n") : 0;
	error == 8 ? ft_printf("Error: start or end\n") : 0;
	error == 10 ? ft_printf("Error: room links to self\n") : 0;
	error == 11 ? ft_printf("Error: no rooms\n") : 0;
	error == 12 ? ft_printf("Error: no links or empty map\n") : 0;
	error == 13 ? ft_printf("Error: no path\n") : 0;
	error == 14 ? ft_printf("Error: link to unknown room\n") : 0;
	error == 15 ? ft_printf("Error: coordinates\n") : 0;
	error == 16 ? ft_printf("Error: duplicate rooms\n") : 0;
	error == 18 ? ft_printf("Error: too many arguments\n") : 0;
	error == 19 ? ft_printf("Error: nom trop grand\n") : 0;
}

void			lem_in_error(t_lemin *e, int error)
{
	if (error > 0)
		error_messages(error);
	else if (error != -2)
		ft_printf("Error\n", 6);
	if (e->i)
		free_info(e);
	free_map1(e);
	free_hash(e);
	if (e->table_r)
		free(e->table_r);
	free_rooms(e->r);
	path_fun_free(e);
	free_ants(e);
	free(e);
	if (error == -2)
		exit(1);
	exit(0);
}

void			print_flag(t_lemin *e, const char **av)
{
	int i;

	i = 1;
	while (av[i])
	{
		if (ft_strequ(av[i], "-v"))
			visu(e);
		else if (ft_strequ(av[i], "-p"))
		{
			ft_printf("\033[36m");
			print_paths(e, e->p);
			ft_printf("\033[37m");
		}
		else
		{
			ft_printf("\033[36m\nutilisation flags:\033[37m\n");
			ft_printf(" 	-v = visu\n 	-p = paths debug\n");
		}
		i++;
	}
}

static void		print_info(t_lemin *e)
{
	t_info *i;

	i = e->i;
	while (i)
	{
		ft_printf("%s\n", i->line);
		if (!i->next)
			break ;
		i = i->next;
	}
	ft_printf("\n");
}

int				main(int ac, char const *av[])
{
	t_lemin *e;

	if ((!(e = ft_memalloc(sizeof(t_lemin)))))
		lem_in_error(e, 1);
	if (ac < 1)
		lem_in_error(e, 1);
	reader(e);
	print_info(e);
	setup_map(e);
	if ((e->max_lines = get_len(e)) == -5)
		lem_in_error(e, 13);
	move_ants_forward(e, e->p, e->a);
	zero_ants(e);
	zero_vistid(e);
	e->stop = -1;
	if (e->p->size_path == 2)
		ft_printf("\n\nsent %d ants directly from start to end\n", e->nb_ants);
	else
		ft_printf("\n\nsent %d ants through %d paths in %d steps\n",
				e->nb_ants, e->nb_paths, e->max_lines);
	print_flag(e, av);
	lem_in_error(e, -2);
	return (0);
}
