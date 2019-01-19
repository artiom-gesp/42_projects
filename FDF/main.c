/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1019/01/17 13:59:04 by agesp             #+#    #+#             */
/*   Updated: 2019/01/19 13:11:23 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	deal_key(int key, void **param)
{
	static int i = 3;
	static int j = 3;
	if (key == 53)
		exit(0);
	else if (key == 12)
	{
		mlx_pixel_put(param[0], param[1], i, j, 0x00FFFF);
		i++;
	}
	else if (key == 13)
	{
		mlx_pixel_put(param[0], param[1], i, j, 0xCC0066);
		j++;
	}
	ft_printf("%d\n", key);
	return (0);
}

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

void	copy_into_tab(int z, int tab[][z], char **tab2)
{
	int i;
	static int y = 0;

	i = 0;
	while (tab2[i])
	{
		tab[i][y] = ft_atoi(tab2[i]);
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

int	get_mouse(int intput, int x, int y, void *param)
{
	static int zoom = 500;
	if (input == 5)
		zoom++;
	else if (input == 4)
		zoom--;
	zoom = zoom > 100 ? 100 : zoom; 
	zoom = zoom < 2 ? 2 : zoom;
	(t_fstruct)param->zoom = zoom;
	return (zoom);
}

int	do_stuff(char *file, t_fstruct *p, t_line *line)
{
	int i;
	int j;
	int fd;
	int tab[p->x][p->y];
	char *save;

	i = 0;
	j = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &save) > 0)
	{
		copy_into_tab(p->y, tab, ft_strsplit(save, ' '));
	}
	i = 0;
	j = 0;
	while (i < p->y)
	{
		j = 0;
		while (j < p->x - 1)
		{
			line->xi = (j - i) * (1000 / p->x) + (p->x * 3);
			line->xf = (j - i + 1) * (1000 / p->x) + (p->x * 3);
			line->yi = (j + i) * (500 / p->x) + 1 - tab[j][i];
			line->yf = (j + i + 1) * (500 / p->x) + 1 - tab[j + 1][i];
			line->color = 0xCC00CC + tab[j][i] * 20000;
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
			line->xi = (i - j) * (1000 / p->x) + (p->x * 3);
			line->xf = (i - (j + 1)) * (1000 / p->x) + (p->x * 3);
			line->yi = (j + i) * (500 / p->x) + 1 - tab[i][j];
			line->yf = (j + i + 1) * (500 / p->x) + 1 - tab[i][j + 1];
			line->color = 0xCC00CC + tab[i][j] * 20000;
			print_seg(line, p);
			j += 1;
		}
	
		i += 1;
	}
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
	p->win = mlx_new_window(p->init, p->x > 100 ? p->x * 10 : 1000, p->y > 100 ? p->y * 10 : 1000, "test");
	mlx_mouse_hook(p->win, p->zoom = get_mouse, p);
	do_stuff(av[1], p, line);
	
	mlx_loop(p->init);
}
