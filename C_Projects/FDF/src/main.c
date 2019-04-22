/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1019/01/17 13:59:04 by agesp             #+#    #+#             */
/*   Updated: 2019/01/27 12:55:57 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			create_list(t_fstruct *p, char *file)
{
	p->x = -1;
	p->y = 0;
	if (!create_tab(file, p))
		return (0);
	p->init = mlx_init();
	p->win = mlx_new_window(p->init, 5000, 5000, "test");
	p->zoom = p->x > 50 ? 1000 / p->x : 30;
	p->max = get_max(p);
	p->min = get_min(p);
	return (1);
}

static void	usage(int flag, t_fstruct *p, t_line *line)
{
	if (flag)
	{
		p ? free(p) : do_nothing();
		line ? free(line) : do_nothing();
	}
	ft_printf("usage: ./fdf [-i or -p] [file]\n");
	ft_printf("file format: x x x\n");
	ft_printf("             x x x\n");
	exit(1);
}

static void	wrong_file(char *file, t_fstruct *p)
{
	ft_printf("Incorrect file : %s\n", file);
	free(p);
	exit(1);
}

static void	print_fdf(char *file, t_fstruct *p, t_line *line)
{
	if (ft_strcmp(file, "-p") == 0)
		print_para(p, line);
	else if (ft_strcmp(file, "-i") == 0)
		print_iso(p, line);
	else
		usage(1, p, line);
}

int			main(int ac, char **av)
{
	t_fstruct	*p;
	t_line		*line;

	line = NULL;
	p = NULL;
	if (ac == 3)
	{
		if (!(p = malloc(sizeof(t_fstruct))))
			return (0);
		if (!(create_list(p, av[2])))
			wrong_file(av[2], p);
		if (!(line = malloc(sizeof(t_line))))
			wrong_file(av[2], p);
		ft_printf("Choose contrast:");
		scanf("%d", &p->contrast);
		print_fdf(av[1], p, line);
		free(line);
		mlx_key_hook(p->win, deal_key, (void*)0);
		mlx_loop(p->init);
		mlx_destroy_window(p->init, p->win);
		free(p);
	}
	else
		usage(0, p, line);
	return (0);
}
