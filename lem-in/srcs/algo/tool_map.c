/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecosmon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:37:44 by kecosmon          #+#    #+#             */
/*   Updated: 2019/04/05 11:30:50 by agesp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

static void			view_coor(t_rooms *r, t_mlx *v)
{
	int i;

	i = -1;
	v->color = 0xfbc531;
	v->d = init_design(r->x, r->y, r->y + 30, r->x + 30);
	function_color(v->d, v);
	v->color = 0x000000;
	v->d = init_design(r->x + 2, r->y + 2, r->y + 28, r->x + 28);
	function_color(v->d, v);
	while (++i < r->nb_links)
	{
		if (r->links[i])
			view_link(r, r->links[i], v);
		else
			break ;
	}
}

void				view_link(t_rooms *r, t_rooms *r2, t_mlx *v)
{
	t_design	*d;
	t_point		p;

	if (!(d = init_design(r->x, r->y, r2->y, r2->x)))
		free_visu(v);
	v->color = 0xe1b12c;
	p.dx = d->fx - d->x;
	p.dy = d->fy - d->y;
	p.xinc = (p.dx > 0) ? 1 : -1;
	p.yinc = (p.dy > 0) ? 1 : -1;
	p.dx = ft_abs(p.dx);
	p.dy = ft_abs(p.dy);
	if (p.dx < p.dy)
		draw_bresehamb(v, d, p);
	else
		draw_breseham(v, d, p);
	free(d);
}

void				init_r(t_mlx *v, int size_path, int *path, int spacey)
{
	int i;
	int spacew;

	spacew = WIDTH / size_path;
	i = 1;
	ft_abs(spacew);
	while (i < size_path - 1)
	{
		v->e->table_r[path[i]]->x = spacew * i;
		v->e->table_r[path[i]]->y = spacey;
		i++;
	}
}

int					init_start(t_mlx *v, int spacew)
{
	v->e->start->y = HEIGHT / 2 + 10;
	v->e->start->x = 50;
	v->e->end->y = HEIGHT / 2;
	v->e->end->x = WIDTH - 100;
	v->tmpspace = HEIGHT / v->e->nb_paths;
	if (v->tmpspace == HEIGHT)
		v->tmpspace = HEIGHT / 2;
	v->hspace = v->tmpspace + 50;
	if (v->e->nb_rooms > 100)
		spacew = WIDTH / 100;
	else
		spacew = WIDTH / 20;
	return (spacew);
}

void				rooms_links(t_mlx *v, t_rooms *r, int i, int spacew)
{
	while (r)
	{
		if (r->x == 0 && r->y == 0)
		{
			v->e->table_r[r->id_r]->y = 150;
			v->e->table_r[r->id_r]->x = spacew * i;
		}
		i++;
		r = r->next;
	}
	r = v->e->r;
	while (r)
	{
		view_coor(r, v);
		r = r->next;
	}
}
