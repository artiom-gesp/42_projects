/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1019/01/17 13:59:04 by agesp             #+#    #+#             */
/*   Updated: 2019/01/22 16:32:07 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_pause(int pause)
{
	int i;

	i = 0;
	while (pause)
	{
		while (i < 100000)
		{
			free(malloc(1));
			i++;
		}
		pause--;
	}
}

static int get_min(t_fstruct *p)
{
	int i;
	int j;
	int ret;

	i = 0;
	ret = p->tab[0][0];
	while (i < p->x)
	{
		j = 0;
		while (j < p->y)
		{
			if (p->tab[i][j] < ret)
				ret = p->tab[i][j];
			j++;
		}
		i++;
	}
	return (ret);
}

static int get_max(t_fstruct *p)
{
	int i;
	int j;
	int ret;

	i = 0;
	ret = p->tab[0][0];
	while (i < p->x)
	{
		j = 0;
		while (j < p->y)
		{
			if (p->tab[i][j] > ret)
				ret = p->tab[i][j];
			j++;
		}
		i++;
	}
	return (ret);
}

int	deal_key(int key, void *param)
{
	(void)param;
	if (key == 53)
		exit(1);
	return (0);
}

int		create_list(t_fstruct *p, char *file)
{
	p->init = mlx_init();
	p->x = -1;
	p->y = 0;
	if (!create_tab(file, p))
		return (0);
	p->win = mlx_new_window(p->init, 5000, 5000, "test");
	p->zoom = p->x > 50 ? 1000 / p->x : 30;
	p->max = get_max(p);
	p->min = get_min(p);
	return (1);
}

static void	usage(void)
{
	ft_printf("usage: ./fdf [-i or -p] [file]\n");
	ft_printf("file format: x x x\n");
	ft_printf("             x x x\n");
	exit(1);
}

static void	wrong_file(char *file)
{
	ft_printf("Incorrect file : %s\n", file);
	exit(1);
}

static void	print_fdf(char *file, t_fstruct *p, t_line *line)
{
	if (ft_strcmp(file, "-p") == 0)
		print_para(p, line);
	else if (ft_strcmp(file, "-i") == 0)
		print_iso(p, line);
	else
		usage();
}

int	main(int ac, char **av)
{
	t_fstruct *p;
	t_line *line;

	line = NULL;
	p = NULL;
	if (ac == 3)
	{
		if (!(p = malloc(sizeof(t_fstruct))))
			return (0);
		if (!(create_list(p, av[2])))
			wrong_file(av[2]);
		if (!(line = malloc(sizeof(t_line))))
			return (0);
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
		usage();
	return (0);
}
