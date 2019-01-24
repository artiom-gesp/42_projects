/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 17:58:07 by agesp             #+#    #+#             */
/*   Updated: 2019/01/24 18:27:48 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "mlx.h"

void	print_result(t_push *a)
{
	if (is_full(a) && is_sorted(a))
	{
		ft_printf("OK\n");
		return ;
	}
	ft_printf("KO\n");
}

int		me_loop(t_libx *p)
{
	char *line;

	if (get_next_line(0, &line) < 1)
	{
		sleep(4);
		print_result(p->a);
		free_list(p->a);
		free_list(p->b);
		free(line);
		exit(1);
	}
	if (!do_check(p->a, p->b, line))
	{
		free_list(p->a);
		free_list(p->b);
		free(line);
		exit(1);
	}
	free(line);
	print_plist(p);
	return (0);
}

int		normal_check(t_push *a, t_push *b)
{
	char	*line;

	line = NULL;
	if (get_nb_elem(a) != 1)
	{
		while (get_next_line(0, &line) > 0)
		{
			if (!do_check(a, b, line))
			{
				free(line);
				free_list(a);
				free_list(b);
				return (0);
			}
			free(line);
		}
	}
	free(line);
	print_result(a);
	free_list(a);
	free_list(b);
	return (1);
}

int		visu_print(t_push *a, t_push *b)
{
	t_libx	*p;

	if (!(p = malloc(sizeof(t_libx))))
		return (0);
	p->a = a;
	p->b = b;
	p->init = mlx_init();
	p->win = mlx_new_window(p->init, 1030, get_list_len(p->a) + 40, "coucou");
	mlx_loop_hook(p->init, me_loop, p);
	mlx_loop(p->init);
	return (1);
}

int		main(int ac, char **av)
{
	t_push	*a;
	t_push	*b;
	char	**tab;
	int		save_ac;

	save_ac = ac;
	tab = create_tab(ac, av);
	if (tab)
		ac = len_tab(tab);
	if (ac > 1)
	{
		if ((save_ac == ac && is_input_ok(ac, av))
				|| (tab && is_input_ok(ac, tab)))
		{
			a = fill_pile(ac, tab ? tab : av, 1);
			b = fill_pile(ac, tab ? tab : av, 0);
			if (!ft_strcmp(av[1], "-v"))
				visu_print(a, b);
			else
				normal_check(a, b);
		}
		else
			ft_printf("Error\n");
	}
	return (0);
}