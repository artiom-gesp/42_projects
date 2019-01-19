/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1019/01/17 13:59:04 by agesp             #+#    #+#             */
/*   Updated: 2019/01/19 17:12:52 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	print_tab(void **param)
{
	int i;
	int j;

	mlx_pixel_put(param[0], param[1], i, j, 0xCC0066);
	return (0);
}

int	get_tab_len(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	is_tab_ok(char **tab, int x)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (!ft_isdigit(tab[i][0]) && (tab[i][0] != '-' && tab[i][1] && !ft_isdigit(tab[i][1])))
			return (0);
		i++;
	}
	if (i != x && x != -1)
		return (0);
	return (1);
}

void	copy_into_tab(int tab[5000][5000], char **tab2)
{
	int i;
	static int y = 0;

	i = 0;
	while (tab2[i])
	{
		tab[i][y] = ft_atoll(tab2[i]);
		i++;
	}
	y++;
}

void	print_square(void **param, int x, int y, long long color)
{
	int i;
	int j;

	i = x;
	j = y;
	mlx_pixel_put(param[0], param[1], i, j, color);
}

int	do_stuff(char *file, t_fstruct *p, t_line *line)
{
	int i;
	int j;
	char *save;

	i = 0;
	j = 0;
	while (i < p->y)
	{
		j = 0;
		while (j < p->x - 1)
		{
			line->xi = (j - i) * (p->zoom) + (p->x > 50 ? sqrt(ft_pow(p->x * 10, 2) + ft_pow(p->y, 2)) / 4: 150);
			line->xf = (j - i + 1) * (p->zoom) + (p->x > 50 ? sqrt(ft_pow(p->x * 10, 2) + ft_pow(p->y, 2)) / 4: 150);
			line->yi = (j + i) * (p->zoom / 2) + (p->y > 50 ? 100 : 20) - p->tab[j][i];
			line->yf = (j + i + 1) * (p->zoom / 2) + (p->y > 50 ? 100 : 20) - p->tab[j + 1][i];
			line->color = 0xBE58F9 + ft_pow(p->tab[j][i], 8);	
			print_seg(line, p);
			j += 1;
		}
		i += 1;
	}
	i = 0;
	j = 0;
	while (i < p->x)
	{
		j = 0;
		while (j < p->y - 1)
		{
			line->xi = (i - j) * (p->zoom) + (p->x > 50 ? sqrt(ft_pow(p->x * 10, 2) + ft_pow(p->y, 2)) / 4 : 150);
			line->xf = (i - (j + 1)) * (p->zoom) + (p->x > 50 ? sqrt(ft_pow(p->x * 10, 2) + ft_pow(p->y, 2)) / 4 : 150); 
			line->yi = (j + i) * (p->zoom / 2) + (p->y > 50 ? 100 : 20) - p->tab[i][j];
			line->yf = (j + i + 1) * (p->zoom / 2) + (p->y > 50 ? 100 : 20) - p->tab[i][j + 1];
			line->color = 0xBE58F9 + ft_pow(p->tab[i][j], 8);
			print_seg(line, p);
			j += 1;
		}
		i += 1;
	}
	return (0);
}
/*
   int	get_mouse(int input, int x, int y, t_fstruct *p)
   {
   ft_printf("%d\n", p->zoom);
   do_stuff(p->save, p, p->line);
   return (zoom);
   }*/

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

int	deal_key(int key, t_fstruct *p)
{
	static int zoom = 50;

	if (key == 126)
		zoom++;
	else if (key == 125)
		zoom--;

	zoom = zoom > 100 ? 100 : zoom; 
	zoom = zoom < 2 ? 2 : zoom;
	p->zoom = zoom;
	return (0);
}

int	main(int ac, char **av)
{
	char	**tab;
	char	*save;
	int		fd;
	t_fstruct *p;
	t_line *line;

	if (!(p = malloc(sizeof(t_fstruct))))
		return (0);
	if (!(line = malloc(sizeof(t_line))))
		return (0);
	fd = open(av[1], O_RDONLY);
	p->init = mlx_init();
	p->x = -1;
	p->y = 0;
	while (get_next_line(fd, &save) > 0)
	{
		tab = ft_strsplit(save, ' ');
		if (!is_tab_ok(tab, p->x))
			return (0);
		p->x = get_tab_len(tab);
		p->y++;
	}
	close(fd);
	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &save) > 0)
	{
		copy_into_tab(p->tab, ft_strsplit(save, ' '));
	}
	if (p->x > 50)
		p->win = mlx_new_window(p->init, sqrt(ft_pow(p->x * 10, 2) + ft_pow(p->y, 2)), sqrt(ft_pow(p->x * 10, 2)), "test");
	else
		p->win = mlx_new_window(p->init, 500, 500, "test");
	//p->win = mlx_new_window(p->init, p->x > 80 ? sqrt(ft_pow(p->x * 20, 2) + ft_pow(p->y, 2)) : 1500, p->y > 80 ? sqrt(ft_pow(p->x * 20, 2) + ft_pow(p->y, 2)): 1500, "test");
	p->zoom = p->x > 40 ? 1000 / p->x : 20;

	do_stuff(av[1], p, line);
	mlx_loop(p->init);
}
