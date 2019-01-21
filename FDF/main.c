/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1019/01/17 13:59:04 by agesp             #+#    #+#             */
/*   Updated: 2019/01/21 18:12:03 by agesp            ###   ########.fr       */
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
	if (p->x > 50)
		p->win = mlx_new_window(p->init, ft_sqrt(ft_pow(p->x * 10, 2)
					+ ft_pow(p->y, 2)), ft_sqrt(ft_pow(p->x * 10, 2)), "test");
	else
		p->win = mlx_new_window(p->init, 1500, 1500, "test");
	return (1);
}

int	main(int ac, char **av)
{
	t_fstruct *p;
	t_line *line;

	if (!(p = malloc(sizeof(t_fstruct))))
		return (0);
	line = NULL;
	if (ac == 2)
	{
		if (!(create_list(p, av[1])))
			return (0);
		if (!(line = malloc(sizeof(t_line))))
			return (0);
		p->zoom = p->x > 50 ? 1000 / p->x : 30;
		p->max = get_max(p);
		p->min = get_min(p);
		get_min(p);
		print_para(p, line);
		free(line);
		mlx_key_hook(p->win, deal_key, (void*)0);
		mlx_loop(p->init);
		mlx_destroy_window(p->init, p->win);
		free(p);
	}
	return (0);
}
