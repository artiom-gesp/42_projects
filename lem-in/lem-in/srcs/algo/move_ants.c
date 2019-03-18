/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agesp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:31:29 by agesp             #+#    #+#             */
/*   Updated: 2019/03/11 17:22:57 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		int_chr(int *tab1, int *tab2, int len)
{
	int x;
	int y;

	x = 1;
	while (x < len)
	{
		y = 1;
		while (y < (len - 1))
		{
			if (tab1[x] == tab2[y])
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

int		is_ok_path(t_lemin *e, t_path *save, t_path *select)
{
	int x;

	if (e->x == 0)
		return (1);
	x = 0;
	while (x < e->x)
	{
		if (!int_chr(select->path, save->path, e->p->size_path))
			return (0);
		if (!select->next)
			break ;
		select = select->next;
		x++;
	}
	return (1);
}

void	add_npath(t_lemin *e, t_path *select, t_path *save, int *nb_of_sp)
{
	e->y = 0;
	if (is_ok_path(e, save, select))
	{
		if (select->path)
		{
			while (select->next)
				select = select->next;
			if (!(select->next = malloc(sizeof(t_path))))
				exit(-1);
			select = select->next;
		}
		if (!(select->path = malloc(sizeof(int) * e->p->size_path)))
			exit(-1);
		select->next = NULL;
		while (e->y < e->p->size_path)
		{
			select->path[e->y] = save->path[e->y];
			e->y++;
		}
		e->x++;
		select->size_path = e->p->size_path;
		*nb_of_sp += 1;
	}
}

int	select_good_paths(t_lemin *e)
{
	t_path *save;
	int	nb_of_sp;
	int	shortest;
	t_path *select_p;
	
	nb_of_sp = 0;
	save = e->p;
	e->x = 0;
	shortest = e->p->size_path;
	if (!(select_p = malloc(sizeof(t_path))))
		exit(-1);
	select_p->path = NULL;
	select_p->next = NULL;
	while (save && save->size_path == shortest && nb_of_sp < e->nb_ants)
	{
		add_npath(e, select_p, save, &nb_of_sp);
		save = save->next;
	}
	e->x = 0;
	e->select_p = select_p;
	while (e->x < nb_of_sp)
	{
		e->y = 0;
		while (e->y < e->p->size_path)
		{
			ft_printf("%d ", select_p->path[e->y]);
			e->y++;
		}
		ft_printf("\n");
		select_p = select_p->next;
		e->x++;
	}
	return (nb_of_sp);
}

int		nbr_len(int nbr)
{
	int i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char	***create_saa(t_lemin *e, int nb_of_sp)
{
	char	***cr_saa;
	int		extension;

	cr_saa = NULL;
	extension = nb_of_sp < e->nb_ants ? e->nb_ants - nb_of_sp : 0;
	if (!(cr_saa = malloc(sizeof(char**) * e->nb_ants)))
		exit(-1);
	e->x = 0;
	while (e->x < e->nb_ants)
	{
		if (!(cr_saa[e->x] = malloc(sizeof(char*) * e->p->size_path + extension)))
			exit(-1);
		e->x++;
	}
	e->x = 0;
	return (cr_saa);
}

char	*create_mask(t_lemin *e, int pos_ant, t_path *p)
{
	int			i;
	char		***saa;
	char		*tmp;

	i = 0;
	while (i < p->size_path)
	{
		if (!(e->saa[e->x][i] = malloc(sizeof(char) * 2 + nbr_len(p->path[i]) + nbr_len(pos_ant))))
			exit(-1);
		ft_bzero(e->saa[e->x][i], sizeof(char) * 2 + nbr_len(p->path[i] + nbr_len(pos_ant)));
		ft_strcat(e->saa[e->x][i], "L");
		ft_strcat(e->saa[e->x][i], tmp = ft_itoa(pos_ant));
		free(tmp);
		ft_strcat(e->saa[e->x][i], "-");
		ft_strcat(e->saa[e->x][i], tmp = ft_itoa(p->path[i]));
		free(tmp);
		i++;
	}
	return (NULL);
}

void	simple_move(t_lemin *e)
{
	int		short_path;
	int		nb_of_sp;
	int		pos_ant;
	t_path	*save;
	
	pos_ant = 1;
	short_path = e->p->size_path;
	nb_of_sp = select_good_paths(e);
	e->x = 0;
	save = e->select_p;
	e->saa = create_saa(e, nb_of_sp);
	while (e->x < e->nb_ants)
	{
		create_mask(e, pos_ant, save);
		if (!save->next)
			save = e->select_p;
		else
			save = save->next;
		pos_ant++;
		e->x++;
	}
	e->x = 0;
	ft_printf("\n");
	while (e->x < e->select_p->size_path)
	{
		e->y = 0;
		while (e->y < e->nb_ants)
		{
			ft_printf("%s ", e->saa[e->y][e->x]);
			e->y++;
		}
		ft_printf("\n");
		e->x++;
	}
}

void	complex_move(t_lemin *e)
{}

void	move_ants_forward(t_lemin *e)
{
	if (e->nb_ants <= e->p->size_path)
		simple_move(e);
	else
		complex_move(e);
}
