/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 17:58:07 by agesp             #+#    #+#             */
/*   Updated: 2019/01/24 15:05:20 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "mlx.h"

static void	print_result(t_push *a)
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
		exit(1);
	}
	if (!do_check(p, line))
		exit(1);
	print_plist(p);
	return (0);
}

int		main(int ac, char **av)
{
	t_push *a;
	t_push *b;
	int		flag;
	char 	**tab;
	int		save_ac;
	t_libx	*p;

	save_ac = ac;
	flag = 0;
	tab = NULL;
	if (!(p = malloc(sizeof(t_libx))))
		return (0);
	if (ac == 3 && !ft_strcmp(av[1], "-v"))
	{
		tab = ft_strsplit(av[2], ' ');
		ac = len_tab(tab);
	}
	else if (ac == 2 && ft_strcmp(av[1], "-v"))
	{
		tab = ft_strsplit(av[1], ' ');
		ac = len_tab(tab);
	}
	if (ac > 1)
	{
		p->init = mlx_init();
		p->win = mlx_new_window(p->init, 1500, 1500, "coucou");
		if ((save_ac == ac && is_input_ok((int)ac, av)) || (tab && is_input_ok(ac, tab)))
		{
			a = fill_pile(ac, tab ? tab : av, 1);
			b = fill_pile(ac, tab ? tab : av, 0);
			p->a = a;
			p->b = b;
			if (!ft_strcmp(av[1], "-v"))
				flag = 1;
			mlx_loop_hook(p->init, me_loop, p);
			mlx_loop(p->init);
		}
		else
			ft_printf("Error\n");
	}
	return (0);
}
